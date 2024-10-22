#include "TUDPClient.h"

using namespace ws2;

TUDPClient::TUDPClient() 
  : TUDPBase<TUDPClient>(), _status(status::disconnected)
{}//-----------------------------------------------------------------


//TUDPClient::TUDPClient(const char* host, uint16_t port)
//  : TUDPBase<TUDPClient>(), _status(status::disconnected)
//{
//  try { ConnectTo(host, port); }
//  catch (std::exception& e) { throw e; }
//}//------------------------------------------------------------------


TUDPClient::TUDPClient(
  //const char* host,
  //uint16_t port,
  size_t size_parsel,
  handler_function_t handler_func,
  handler_exception_t handler_except
) : TUDPBase<TUDPClient>(size_parsel), _status(status::disconnected)
{
  try {
    //ConnectTo(host, port);
    SetHandler(size_parsel, handler_func, handler_except);
  }
  catch (std::exception& e) { throw e; }
}//------------------------------------------------------------------


TUDPClient::~TUDPClient() noexcept {
  Disconnect();
}//------------------------------------------------------------------


TUDPClient::SocketType TUDPClient::Type() const {
  return SocketType::client_socket;
}//------------------------------------------------------------------


//TUDPClient::status TUDPClient::ConnectTo(const char* host, uint16_t port) {
//  try {
//    if (_status == status::connected) {
//      Disconnect();
//      CreateSocket();
//      _status == status::socket_init;
//    }
//
//    SocketAddr_in address = std::move(CreateAddess(host, port));
//
//    if (connect(_socket, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
//      _status = status::err_socket_connect;
//
//      WSADescriptionErr descr(WSAGetLastError());
//      throw std::exception(descr.GetFullDescr(
//        "TUDPClient::ConnectTo() (connect failed)").c_str());
//    }
//
//    return _status = status::connected;
//  }
//  catch (std::exception& e) { throw e; }
//}//------------------------------------------------------------------


TUDPClient::status TUDPClient::Disconnect() {
  try {
    if (_status != status::connected && _status != status::socket_init)
      return _status;

    JoinHandler();
   
    if (shutdown(_socket, SD_BOTH) == SOCKET_ERROR) {
      WSADescriptionErr descr(WSAGetLastError());
      throw std::logic_error(descr.GetFullDescr(
        "TUDPClient::Disconnect() (shutdown failed)"));
    }

    CloseSocket();

    return _status = status::disconnected;
  }
  catch (std::exception& e) { throw e; }
}//------------------------------------------------------------------


//bool TUDPClient::SendData(const void* buffer, size_t size) {
//  if (_status != status::connected)
//    return false;
//
//  try {
//    //void* send_buffer = malloc(size);
//    //memcpy(reinterpret_cast<char*>(send_buffer), buffer, size);
//
//    int send_byte = send(
//      _socket, reinterpret_cast<char*>(const_cast<void*>(buffer)), size, 0
//    );
//
//    //free(send_buffer);
//
//    if (send_byte == SOCKET_ERROR) {
//      _status = status::err_socket_connect;
//      WSADescriptionErr descr(WSAGetLastError());
//      throw std::exception(descr.GetFullDescr(
//        "TUDPClient::SendData() (send failed)").c_str());
//    }
//
//    return true;
//  }
//  catch (std::exception& e) { throw e; }
//}//------------------------------------------------------------------


void TUDPClient::SendDataTo(
  const char* host, uint16_t port, const void* buffer, size_t size)
{
  try {
    SocketAddr_in address = std::move(CreateAddess(host, port));
    TUDPBase<TUDPClient>::SendDataTo(
      address, sizeof(address), buffer, size
    );

    if (_status == status::disconnected) {
      _address = address;
      _status = status::connected;
    }
  }
  catch (std::exception& e) { throw e; }
}//------------------------------------------------------------------


void TUDPClient::SendDataTo(
  SocketAddr_in& address, SockLen_t addr_len, 
  const void* buffer, size_t size)
{
  try {
    TUDPBase<TUDPClient>::SendDataTo(address, addr_len, buffer, size);

    if (_status == status::disconnected) {
      _address = address;
      _status = status::connected;
    }
  }
  catch (std::exception& e) { throw e; }
}//------------------------------------------------------------------


bool TUDPClient::Compare(const char* host, uint16_t port) {
  try {
    if (_status == status::connected) {
      SocketAddr_in address = std::move(CreateAddess(host, port));

      if (_address.sin_port == address.sin_port
        && _address.sin_addr.s_addr == address.sin_addr.s_addr)
      {
        return true;
      }
    }

    return false;
  }
  catch (std::exception& e) { throw e; }
}//------------------------------------------------------------------


void TUDPClient::CloseSocket() {
  _status = status::disconnected;
  TUDPBase<TUDPClient>::CloseSocket();
}//------------------------------------------------------------------


std::string TUDPClient::GetHost() const {
  if (_status == status::connected)
    return std::string(inet_ntoa(_address.sin_addr));

  return std::string{ "" };
}//------------------------------------------------------------------


uint32_t TUDPClient::GetHostSIN() const {
  if (_status == status::connected)
    return _address.sin_addr.S_un.S_addr;

  return INADDR_NONE;
}//------------------------------------------------------------------


uint16_t TUDPClient::GetPort() const {
  if (_status == status::connected)
    return ntohs(_address.sin_port);

  return 0;
}//------------------------------------------------------------------


uint16_t TUDPClient::GetPortSIN() const {
  if (_status == status::connected)
    return _address.sin_port;

  return 0;
}//------------------------------------------------------------------


TUDPClient::status TUDPClient::GetStatus() const {
  return _status;
}//------------------------------------------------------------------
