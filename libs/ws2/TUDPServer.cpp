#include "TUDPServer.h"

using namespace ws2;

TUDPServer::TUDPServer(
	uint16_t port,
	size_t size_parsel, 
	handler_function_t handler_func, 
	handler_exception_t handler_except
) : TUDPBase<TUDPServer>(size_parsel)
{
    try {
        SetPortAndStart(port, size_parsel, handler_func, handler_except);
	}
	catch (std::exception& except) { throw except; }
}//------------------------------------------------------------------


TUDPServer::~TUDPServer() {
	if (_status == status::up) Stop();
}//------------------------------------------------------------------


TUDPServer::SocketType TUDPServer::Type() const {
	return SocketType::server_socket;
}//------------------------------------------------------------------


void TUDPServer::SetPortAndStart(
	uint16_t port, 
	size_t size_parsel,
	handler_function_t handler_func,
	handler_exception_t handler_except) 
{
	try {
		if (_status == status::up) {
			Stop();
			CreateSocket();
		}

		// Set reuse socket
		if (int flag = true;
			setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(flag)) == SOCKET_ERROR)
		{
			_status = status::err_socket_reuse;
			WSADescriptionErr descr(WSAGetLastError());

			CloseSocket();

            throw std::logic_error(descr.GetFullDescr(
                "TUDPServer::SetPortAndStart() (setsockopt failed)"));
		}

		_address = CreateAnyAddess(port);

		// Bind address to socket
		if (bind(_socket, (struct sockaddr*)&_address, sizeof(_address)) == SOCKET_ERROR) {
			_status = status::err_socket_bind;
			WSADescriptionErr descr(WSAGetLastError());

			CloseSocket();

            throw std::logic_error(descr.GetFullDescr(
                "TUDPServer::SetPortAndStart() (bind failed)"));
		}

		_status = status::up;

		SetHandler(size_parsel, handler_func, handler_except);
	}
	catch (std::exception& except) { throw except; }
}//------------------------------------------------------------------


TUDPServer::status TUDPServer::Stop() {
	try {
		if (_status != status::up)
			return _status;

		JoinHandler();

		if (shutdown(_socket, SD_BOTH) == SOCKET_ERROR) {
			WSADescriptionErr descr(WSAGetLastError());
            throw std::logic_error(descr.GetFullDescr(
                "TUDPClient::Disconnect() (shutdown failed)"));
		}

		CloseSocket();

		return _status = status::close;
	}
	catch (std::exception& e) { throw e; }
}//------------------------------------------------------------------


bool TUDPServer::sendDataTo(
	const char* host, uint16_t port, 
	const void* buffer, const size_t size)
{
	try {
		if (_status == status::up) {
			SocketAddr_in address = std::move(CreateAddess(host, port));
			TUDPBase<TUDPServer>::SendDataTo(
				address, sizeof(SocketAddr_in), buffer, size
			);

			return true;
		}
		return false;
	}
	catch (std::exception& except) { throw except; }
}//------------------------------------------------------------------


bool TUDPServer::sendDataTo(
	SocketAddr_in& address, SockLen_t addr_len,
	const void* buffer, const size_t size)
{
	try {
		if (_status == status::up) {
			TUDPBase<TUDPServer>::SendDataTo(
				address, addr_len, buffer, size
			);

			return true;
		}
		return false;
	}
	catch (std::exception& except) { throw except; }
}//------------------------------------------------------------------


uint16_t TUDPServer::GetPort() const {
	return ntohs(_address.sin_port);
}//------------------------------------------------------------------


TUDPServer::status TUDPServer::GetStatus() const {
	return _status;
}//------------------------------------------------------------------
