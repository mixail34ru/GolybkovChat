#include "WSADescriptionErr.h"
#include "ws2define.h"

using namespace ws2;

WSADescriptionErr::WSADescriptionErr(int code) : _code(code) {
}//------------------------------------------------------------------


int WSADescriptionErr::Code() const {
  return _code;
}//------------------------------------------------------------------


WSADescriptionErr::Description_t WSADescriptionErr::Description() const {
  Description_t d;

  switch (_code) {
  case /* 0     */ 0:
    d.name = "Не ошибка";
    d.descr = "Код ошибки отсутствует.";
    break;
  case /* 6     */ WSA_INVALID_HANDLE:
    d.name = "WSA_INVALID_HANDLE";
    d.descr = "Одно или несколько значений в массиве lphEvents "
      "не являются допустимым дескриптором объекта события.";
    break;
  case /* 8     */ WSA_NOT_ENOUGH_MEMORY:
    d.name = "WSA_NOT_ENOUGH_MEMORY";
    d.descr = "Недостаточно свободной памяти для создания объекта "
      "события.";
    break;
  case /* 87    */ WSA_INVALID_PARAMETER:
    d.name = "WSA_INVALID_PARAMETER";
    d.descr = "Параметр cEvents не содержит допустимого количества "
      "дескрипторов.";
    break;
  case /* 10004 */ WSAEINTR:
    d.name = "WSAEINTR";
    d.descr = "Вызов (блокирующий) был отменен через "
      "WSACancelBlockingCall.";
    break;
  case /* 10013 */ WSAEACCES:
    d.name = "WSAEACCES";
    d.descr = "Запрошенный адрес является широковещательным адресом, "
      "но соответствующий флаг не задан. Вызов setsockopt "
      "с параметром SO_BROADCAST, чтобы разрешить использование "
      "широковещательного адреса.";
    break;
  case /* 10014 */ WSAEFAULT:
    d.name = "WSAEFAULT";
    d.descr = "Параметр lpNetworkEvents не является допустимой частью "
      "адресного пространства пользователя.";
    break;
  case /* 10022 */ WSAEINVAL:
    d.name = "WSAEINVAL";
    d.descr = "Один из указанных параметров является недопустимым, "
      "или указанный сокет находится в недопустимом состоянии.";
    break;
  case /* 10024 */ WSAEMFILE:
    d.name = "WSAEMFILE";
    d.descr = "Больше нет доступных дескрипторов сокетов.";
    break;
  case /* 10035 */ WSAEWOULDBLOCK:
    d.name = "WSAEWOULDBLOCK";
    d.descr = "Сокет помечается как неблокировочный, и операция recvfrom "
      "будет блокироваться.";
    break;
  case /* 10036 */ WSAEINPROGRESS:
    d.name = "WSAEINPROGRESS";
    d.descr = "Выполняется блокирующий вызов Windows Sockets 1.1 "
      "или поставщик услуг по-прежнему обрабатывает функцию "
      "обратного вызова.";
    break;
  case /* 10038 */ WSAENOTSOCK:
    d.name = "WSAENOTSOCK";
    d.descr = "Дескриптор не является сокетом.";
    break;
  case /* 10039 */ WSAEDESTADDRREQ:
    d.name = "WSAEDESTADDRREQ";
    d.descr = "Требуется адрес назначения.";
    break;
  case /* 10040 */ WSAEMSGSIZE:
    d.name = "WSAEMSGSIZE";
    d.descr = "Сообщение было слишком большим, чтобы поместиться в буфер, "
      "на который указывает параметр buf, и было усечено.";
    break;
  case /* 10041 */ WSAEPROTOTYPE:
    d.name = "WSAEPROTOTYPE";
    d.descr = "Указанный протокол не поддерживается.";
    break;
  case /* 10042 */ WSAENOPROTOOPT:
    d.name = "WSAENOPROTOOPT";
    d.descr = "Параметр неизвестен или не поддерживается для указанного "
      "поставщика или сокета (см. SO_GROUP_PRIORITY ограничения).";
    break;
  case /* 10043 */ WSAEPROTONOSUPPORT:
    d.name = "WSAEPROTONOSUPPORT";
    d.descr = "Указанный протокол является неправильным типомдля этого "
      "сокета.";
    break;
  case /* 10044 */ WSAESOCKTNOSUPPORT:
    d.name = "WSAESOCKTNOSUPPORT";
    d.descr = "Указанный тип сокета не поддерживается в этом семействе "
      "адресов.";
    break;
  case /* 10045 */ WSAEOPNOTSUPP:
    d.name = "WSAEOPNOTSUPP";
    d.descr = "MSG_OOB указано, но сокет не является типом потока, "
      "например тип SOCK_STREAM, данные OOB не поддерживаются "
      "в домене связи, связанном с этим сокетом, или сокет "
      "является однонаправленным и поддерживает только операции "
      "отправки.";
    break;
  case /* 10047 */ WSAEAFNOSUPPORT:
    d.name = "WSAEAFNOSUPPORT";
    d.descr = "Адреса из заданного семейства адресов не могут "
      "использоваться с этим сокетом.";
    break;
  case /* 10048 */ WSAEADDRINUSE:
    d.name = "WSAEADDRINUSE";
    d.descr = "Локальный адрес сокета уже используется, и сокет "
      "не помечен, чтобы разрешить повторное использование "
      "адресов с SO_REUSEADDR.";
    break;
  case /* 10049 */ WSAEADDRNOTAVAIL:
    d.name = "WSAEADDRNOTAVAIL";
    d.descr = "Удаленный адрес не является допустимым, например ADDR_ANY.";
    break;
  case /* 10050 */ WSAENETDOWN:
    d.name = "WSAENETDOWN";
    d.descr = "Произошел сбой сетевой подсистемы.";
    break;
  case /* 10051 */ WSAENETUNREACH:
    d.name = "WSAENETUNREACH";
    d.descr = "В настоящее время сеть недоступна с этого узла.";
    break;
  case /* 10052 */ WSAENETRESET:
    d.name = "WSAENETRESET";
    d.descr = "Для сокета датаграмм эта ошибка указывает на то, что срок "
      "жизни истек.";
    break;
  case /* 10053 */ WSAECONNABORTED:
    d.name = "WSAECONNABORTED";
    d.descr = "Виртуальное подключение разорвано из-за тайм-аута или иного "
      "сбоя. Приложение должно закрыть сокет, поскольку он больше "
      "не может использоваться.";
    break;
  case /* 10054 */ WSAECONNRESET:
    d.name = "WSAECONNRESET";
    d.descr = "Виртуальное подключение было сброшено удаленной стороной "
      "путем прерывания.Приложение должнозакрыть сокет; "
      "он больше не пригоден дляиспользования. В сокете "
      "UDP - датаграмм эта ошибка указывает на то, что предыдущая "
      "операция отправкипривела к сообщению о недоступности "
      "порта ICMP.";
    break;
  case /* 10055 */ WSAENOBUFS:
    d.name = "WSAENOBUFS";
    d.descr = "Нет свободного места в буфере.";
    break;
  case /* 10056 */ WSAEISCONN:
    d.name = "WSAEISCONN";
    d.descr = "Сокет подключен. Эта функция не разрешена сподключенным "
      "сокетом, независимо от того,ориентирован ли сокет "
      "на подключение или безподключения.";
    break;
  case /* 10057 */ WSAENOTCONN:
    d.name = "WSAENOTCONN";
    d.descr = "Сокет не подключен (только сокеты, ориентированные "
      "на подключение).";
    break;
  case /* 10058 */ WSAESHUTDOWN:
    d.name = "WSAESHUTDOWN";
    d.descr = "Сокет был выключен; После вызова завершения работы "
      "невозможно выполнить восстановление в сокете с параметром "
      "SD_RECEIVE или SD_BOTH.";
    break;
  case /* 10060 */ WSAETIMEDOUT:
    d.name = "WSAETIMEDOUT";
    d.descr = "Подключение было прервано из-за сбоя сети или из-за того, "
      "что система на другом конце не работает "
      "без предварительного уведомления.";
    break;
  case /* 10065 */ WSAEHOSTUNREACH:
    d.name = "WSAEHOSTUNREACH";
    d.descr = "В настоящее время удаленный узел не может бытьдостигнут "
      "из этого узла.";
    break;
  case /* 10067 */ WSAEPROCLIM:
    d.name = "WSAEPROCLIM";
    d.descr = "Достигнуто ограничение на количество задач, поддерживаемых "
      "реализацией сокетов Windows.";
    break;
  case /* 10091 */ WSASYSNOTREADY:
    d.name = "WSASYSNOTREADY";
    d.descr = "Базовая сетевая подсистема не готова к сетевому обмену "
      "данными.";
    break;
  case /* 10092 */ WSAVERNOTSUPPORTED:
    d.name = "WSAVERNOTSUPPORTED";
    d.descr = "Запрошенная версия поддержки сокетов Windows "
      "не предоставляется этой конкретной реализацией "
      "сокетов Windows.";
    break;
  case /* 10093 */ WSANOTINITIALISED:
    d.name = "WSANOTINITIALISED";
    d.descr = "Перед использованием этой функции должен произойти "
      "успешный вызов WSAStartup.";
    break;
  case /* 10104 */ WSAEINVALIDPROCTABLE:
    d.name = "WSAEINVALIDPROCTABLE";
    d.descr = "Поставщик служб вернул в WSPStartup недопустимую "
      "или неполную таблицу процедур.";
    break;
  case /* 10105 */ WSAEINVALIDPROVIDER:
    d.name = "WSAEINVALIDPROVIDER";
    d.descr = "Поставщик услуг вернул версию, отличаемую от 2.2.";
    break;
  case /* 10106 */ WSAEPROVIDERFAILEDINIT:
    d.name = "WSAEPROVIDERFAILEDINIT";
    d.descr = "Поставщику услуг не удалось инициализировать. Эта ошибка "
      "возвращается, если поставщик многоуровневой службы (LSP) "
      "или поставщикпространства имен был неправильно установлен "
      "или поставщик не работает правильно.";
    break;
  default:
    d.name = "Неизвестная ошибка";
    d.descr = "Неизвестная ошибка";
    break;
  } //switch

  return d;
}//------------------------------------------------------------------


std::string WSADescriptionErr::Name() const {
  return Description().name;
}//------------------------------------------------------------------


std::string WSADescriptionErr::Descr() const {
  return Description().descr;
}//------------------------------------------------------------------


std::string WSADescriptionErr::GetFullDescr() const {
  Description_t d = Description();
  return
    "Code error: " + d.name + " (" + std::to_string(_code) + ")\n"
    "Description: " + d.descr;
}//------------------------------------------------------------------


std::string WSADescriptionErr::GetFullDescr(std::string prescript) const {
  return prescript + ":\n" + GetFullDescr();
}//------------------------------------------------------------------