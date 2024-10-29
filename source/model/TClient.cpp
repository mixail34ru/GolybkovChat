#include "TClient.h"

#include <QDebug>

TClient::TClient(QObject* parent) : QObject(parent) {
}//------------------------------------------------------------------


TClient::~TClient() {
    StopSendingMessage();
}//------------------------------------------------------------------


void TClient::SendMessage(
    const std::string& host, uint16_t port, const void* buffer, size_t size)
{
    try { _client.SendDataTo(host.c_str(), port, buffer, size); }
    catch (...) { qDebug() << "exception TClient::SendMessage"; }

    emit statusSendingChanged(false);
}//------------------------------------------------------------------


void TClient::StartSendingMessage(
    uint32_t timeout,
    const std::string& host, uint16_t port, const void* buffer, size_t size,
    handler_exception_t hndl_except)
{
    try {
        if (!_timer && timeout > 0) {
            // локальный буфер
            std::shared_ptr<char[]> local_buff(new char[size]);
            memcpy(local_buff.get(), buffer, size);

            _timer = std::make_unique<wstd::timer>(
                std::chrono::milliseconds(timeout),
                [this, timeout, host, port, local_buff, size]() {
                    _client.SendDataTo(host.c_str(), port, local_buff.get(), size);
                    qDebug() << "timeout " << timeout;
                },
                true,
                [this, hndl_except](std::exception_ptr eptr, wstd::timer* timer) {
                    hndl_except(eptr, this);
                }
            );
        }
    }
    catch (...) {
        qDebug() << "exception TClient::StartTimerMessage";
    }

    emit statusSendingTimerChanged(IsTimerSending());
}//------------------------------------------------------------------


void TClient::StopSendingMessage() {
    if (_timer) _timer.reset();
    emit statusSendingTimerChanged(IsTimerSending());
}//------------------------------------------------------------------


bool TClient::IsTimerSending() const {
    return (_timer.get() != nullptr ? true : false);
}//------------------------------------------------------------------
