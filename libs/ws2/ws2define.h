#ifndef WS2DEFINE_H
#define WS2DEFINE_H

#ifdef _WIN32

#include <WinSock2.h>
// Need to link with Ws2_32.lib
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#else
#define SD_BOTH 0
#include <sys/socket.h>
#endif

#include <cstdint>
#include <vector>

namespace ws2 {

#ifdef _WIN32 // Windows NT
	typedef SOCKET socket_t;
	typedef int SockLen_t;
	typedef SOCKADDR_IN SocketAddr_in;
	typedef SOCKET Socket;
	typedef u_long ka_prop_t;
#else // POSIX
	typedef int socket_t;
	typedef socklen_t SockLen_t;
	typedef struct sockaddr_in SocketAddr_in;
	typedef int Socket;
	typedef int ka_prop_t;
#endif

	typedef std::vector<uint8_t> DataBuffer;


#ifdef _WIN32 // Windows NT
namespace {

class _WinSocketIniter {
	static inline WSAData w_data;
public:
	_WinSocketIniter() { WSAStartup(MAKEWORD(2, 2), &w_data); }
	~_WinSocketIniter() { WSACleanup(); }
}; //class _WinSocketIniter

static inline _WinSocketIniter _winsock_initer;
};
#endif //_WIN32

} //namespace ws2

#endif //WS2DEFINE_H
