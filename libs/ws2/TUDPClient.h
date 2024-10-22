#ifndef TUDPCLIENT_H
#define TUDPCLIENT_H

#include "TUDPBase.h"

namespace ws2 {

class TUDPClient : public TUDPBase<TUDPClient> {
public:
	enum class status : uint8_t {
		connected,
		socket_init,
		err_socket_init,
		err_socket_connect,
		disconnected
	}; //enum class SocketStatus

	TUDPClient();

	//TUDPClient(const char* host, uint16_t port);

	TUDPClient(
		//const char* host,
		//uint16_t port,
		size_t size_parsel,
		handler_function_t handler,
		handler_exception_t except_hndl = default_exception_handler
	);

	TUDPClient(TUDPClient&& other) : _status(other._status.load()) {}
	TUDPClient& operator = (TUDPClient&& other) {
		if (this != &other) {
			_status = other._status.load();
		}
		return *this;
	}//----------------------------------------------------------------

	~TUDPClient() noexcept;

	SocketType Type() const override;

	//status ConnectTo(const char* host, uint16_t port);
	status Disconnect();

	//bool SendData(const void* buffer, size_t size);

	void SendDataTo(
		const char* host, uint16_t port, 
		const void* buffer, size_t size
	);

	void SendDataTo(
		SocketAddr_in& address, SockLen_t addr_len,
		const void* buffer, size_t size
	);

	bool Compare(const char* host, uint16_t port);

	std::string GetHost() const;
	uint32_t GetHostSIN() const;
	uint16_t GetPort() const;
	uint16_t GetPortSIN() const;
	status GetStatus() const;

private:
	std::atomic<status> _status = status::disconnected;

	TUDPClient(const TUDPClient&) = delete;
	TUDPClient& operator = (const TUDPClient&) = delete;

	void CloseSocket();

}; //class TUDPClient

} //namespace ws2

#endif //TUDPCLIENT_H