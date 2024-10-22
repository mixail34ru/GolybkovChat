#ifndef TUDPSERVER_H
#define TUDPSERVER_H

#include "TUDPBase.h"

namespace ws2 {

class TUDPServer : public TUDPBase<TUDPServer> {
public:
	enum class status : uint8_t {
		up,
		err_socket_init,
		err_socket_bind,
		err_socket_reuse,
		close
	}; //enum class status

	TUDPServer(
		uint16_t port,
		size_t size_parsel,
		handler_function_t handler,
		handler_exception_t handler_exception = default_exception_handler
	);

	~TUDPServer() noexcept;

	SocketType Type() const override;

	void SetPortAndStart(
		uint16_t port,
		size_t size_parsel,
		handler_function_t handler_func,
		handler_exception_t handler_except = default_exception_handler
	);

	status Stop();

	bool sendDataTo(
		const char* host, uint16_t port,
		const void* buffer, const size_t size
	);

	bool sendDataTo(
		SocketAddr_in& address, SockLen_t addr_len,
		const void* buffer, const size_t size
	);

	uint16_t GetPort() const;

	status GetStatus() const;

private:
	std::atomic<status> _status = status::close;

}; //class TUDPServer

} //namespace ws2

#endif //TUDPSERVER_H