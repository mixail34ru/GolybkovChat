#pragma once
#ifndef TUDPBASE_H
#define TUDPBASE_H

#include "ws2define.h"
#include "WSADescriptionErr.h"

#include <Windows.h>

#include <cstdint>
#include <functional>
#include <thread>
#include <atomic>
#include <stdexcept>

namespace ws2 {

template<typename Derived>
class TUDPBase {
	friend Derived;

public:
	using handler_function_t
		= std::function<void(DataBuffer, SocketAddr_in&, SockLen_t, Derived*)>;
	static constexpr auto default_handler_function
		= [](DataBuffer, SocketAddr_in&, SockLen_t, Derived*) {};

	using handler_exception_t = std::function<void(std::exception_ptr, Derived*)>;
	static constexpr auto default_exception_handler = [](std::exception_ptr, Derived*) {};

	enum class SocketType : uint8_t {
		client_socket = 0,
		server_socket = 1
	}; //enum class SocketType

	virtual SocketType Type() const = 0;


	TUDPBase(TUDPBase&& other) :
		_socket(std::move(other._socket)),
		_event(std::move(other._event)),
		_address(std::move(other._address)),
		_size_parsel(std::move(_size_parsel)),
		_handler_func(other._handler_func),
		_handler_except(other._handler_except),
		_thread(std::move(other._thread)),
		is_listening(other.is_listening.load())
	{}//---------------------------------------------------------------


	TUDPBase& operator = (TUDPBase&& other) {
		if (this != &other) {
			_socket = std::move(other._socket);
			_event = std::move(other._event);
			_address = std::move(other._address);
			_size_parsel = std::move(_size_parsel);
			_handler_func = other._handler_func;
			_handler_except = other._handler_except;
			_thread = std::move(other._thread);
			is_listening = other.is_listening.load();
		}
		return *this;
	}//----------------------------------------------------------------


	virtual ~TUDPBase() noexcept {
	}//-----------------------------------------------------------------


	void SetHandler(size_t size_parsel,
		handler_function_t handler_func,
		handler_exception_t handler_except = default_exception_handler)
	{
		JoinHandler();

		_size_parsel = size_parsel;
		_handler_func = handler_func;
		_handler_except = handler_except;

		is_listening = true;
		_thread = std::make_unique<std::thread>(
			[this] { WaitingDataLoop(); }
		);
	}//------------------------------------------------------------------


	void JoinHandler() {
		if (is_listening) {
			is_listening = false;

			if (WSASetEvent(_event) == FALSE) {
				WSADescriptionErr descr(WSAGetLastError());
                throw std::logic_error(descr.GetFullDescr(
					"TUDPClient::JoinHandler() (WSASetEvent failed)").c_str());
			}

			if (_thread) {
				if (_thread->joinable()) {
					_thread->join();
					_thread.reset();
				}
			}
		}
	}//------------------------------------------------------------------


	SocketAddr_in CreateAddess(const char* host, uint16_t port) {
		SocketAddr_in address;
		address.sin_family = AF_INET;
		address.sin_port = htons(port);

		int iResult = inet_pton(AF_INET, host, &address.sin_addr);
		if (iResult == 0) {
			std::string str = "TUDPBase::CreateAddess() (inet_pton failed):\n";
			std::string IP(host); IP = "IP address: " + IP + " isn't legal.";
            throw std::logic_error((str + IP).c_str());
		}
		else if (iResult == -1) {
			WSADescriptionErr descr(WSAGetLastError());
            throw std::logic_error(descr.GetFullDescr(
                "TUDPBase::CreateAddess() (inet_pton failed)"));
		}

		return address;
	}//------------------------------------------------------------------


	SocketAddr_in CreateAnyAddess(uint16_t port) {
		SocketAddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = ADDR_ANY;
		address.sin_port = htons(port);

		return address;
	}//------------------------------------------------------------------


private:
	socket_t _socket;
	WSAEVENT _event; //!< Описание нового объекта события.
	SocketAddr_in _address;
	size_t _size_parsel;

	handler_function_t _handler_func;
	handler_exception_t _handler_except;

	std::unique_ptr<std::thread> _thread;
	std::atomic<bool> is_listening = false;

	TUDPBase(const TUDPBase&) = delete;
	TUDPBase& operator = (const TUDPBase&) = delete;


	TUDPBase(size_t size_parsel = 0) 
		: _size_parsel(size_parsel), is_listening(false)
	{
		try { CreateSocket(); }
		catch (std::exception& e) { throw e; }
	}//----------------------------------------------------------------


	void CreateSocket() {
		// Create socket
		if ((_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
			WSADescriptionErr descr(WSAGetLastError());
            throw std::logic_error(descr.GetFullDescr(
				"TUDPBase::CreateSocket() (socket failed)").c_str());
		}

		// Create new event object
		if ((_event = WSACreateEvent()) == WSA_INVALID_EVENT) {
			WSADescriptionErr descr(WSAGetLastError());
			CloseSocket();
            throw std::logic_error(descr.GetFullDescr(
                "TUDPBase::CreateSocket() (WSACreateEvent failed)"));
		}

		/* Specifies an event object to be associated with thespecified
			 set of FD_XXX network events */
		if ((WSAEventSelect(_socket, _event, FD_READ)) == SOCKET_ERROR) {
			WSADescriptionErr descr(WSAGetLastError());
			CloseSocket();
            throw std::logic_error(descr.GetFullDescr(
                "TUDPBase::CreateSocket() (WSAEventSelect failed)"));
		}
	}//----------------------------------------------------------------


	void CloseSocket() {
		if (WSACloseEvent(_event) == FALSE) {
			WSADescriptionErr descr(WSAGetLastError());
            throw std::logic_error(descr.GetFullDescr(
                "TUDPBase::CloseSocket() (WSACloseEvent failed)"));
		}

		if (closesocket(_socket) == SOCKET_ERROR) {
			WSADescriptionErr descr(WSAGetLastError());
            throw std::logic_error(descr.GetFullDescr(
                "TUDPBase::CloseSocket() (closesocket failed)"));
		}
	}//----------------------------------------------------------------


	void SendDataTo(
		SocketAddr_in& address, SockLen_t addr_len,
		const void* buffer, size_t size)
	{
		try {
			int send_byte = sendto(
				_socket, reinterpret_cast<char*>(const_cast<void*>(buffer)), 
				size, 0, (sockaddr*)&address, addr_len
			);

			if (send_byte == SOCKET_ERROR) {
				WSADescriptionErr descr(WSAGetLastError());
                throw std::logic_error(descr.GetFullDescr(
                    "TUDPBase::SendDataTo() (sendto failed)"));
			}
		}
		catch (std::exception& e) { throw e; }
	}//----------------------------------------------------------------


	DataBuffer LoadData(SocketAddr_in& address, SockLen_t* addr_len) {
		int nResult;    // Результат выполнения сетевых функций WinAPI (int)
		DWORD dResult;  // Результат выполнения сетевых функций WinAPI (DWORD)
		WSANETWORKEVENTS network_events;  // Создание экземляра описателя событий сокета

		DataBuffer buffer(_size_parsel);

		// Ожидаю событие на сокете
		dResult = WSAWaitForMultipleEvents(1, &_event, false, WSA_INFINITE, false);
		if (dResult == WSA_WAIT_FAILED) {
			WSADescriptionErr descr(WSAGetLastError());
            throw std::logic_error(descr.GetFullDescr(
                "TUDPBase::LoadData (WSAWaitForMultipleEvents failed)"));
		}

		// Получаю структуру, описывающую произошедшее событие
		nResult = WSAEnumNetworkEvents(_socket, _event, &network_events);
		if (nResult == SOCKET_ERROR) {
			WSADescriptionErr descr(WSAGetLastError());
            throw std::logic_error(descr.GetFullDescr(
                "TUDPBase::LoadData (WSAEnumNetworkEvents failed)"));
		}

		// Если это то событие, которое я ожидаю, то читаю полученные данные
		if (network_events.lNetworkEvents & FD_READ) {
			// Получаем датаграмму и сохраняем исходный адрес
			int received_bytes = recvfrom(
				_socket, reinterpret_cast<char*>(buffer.data()), buffer.size(),
				0, (SOCKADDR*)&address, addr_len);

			if (!received_bytes) {
				return DataBuffer();
			}
			else if (received_bytes == SOCKET_ERROR) {
				int err = WSAGetLastError();
				if (!err) {
					SockLen_t len = sizeof(err);
					getsockopt(_socket, SOL_SOCKET, SO_ERROR, (char*)&err, &len);
				}

				switch (err) {
				case 0: return DataBuffer();
					//Keep alive timeout
				case WSAETIMEDOUT:
				case WSAECONNRESET:
					[[fallthrough]];
					// No data
				case WSAEWOULDBLOCK: return DataBuffer();
				default:
					WSADescriptionErr descr(WSAGetLastError());
                    throw std::logic_error(descr.GetFullDescr(
                        "TUDPBase::LoadData (recvfrom failed)"));
				}
			}
		}
		else {
			return DataBuffer();
		}

		return buffer;
	}//------------------------------------------------------------------


	void WaitingDataLoop() {
		try {
			SocketAddr_in address;
			SockLen_t addr_len = sizeof(address);

			while (is_listening) {
				if (DataBuffer data = LoadData(address, &addr_len); !data.empty()) {
					_handler_func(
						std::move(data), address, addr_len, static_cast<Derived*>(this)
					);
				}
			}
		}
		catch (...) {
			_handler_except(
				std::move(std::current_exception()), static_cast<Derived*>(this)
			);
		}
	}//----------------------------------------------------------------

}; //class TUDPBase

} //namespace ws2

#endif //TUDPBASE_H
