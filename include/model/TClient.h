#ifndef TCLIENT_H
#define TCLIENT_H

#include "TUDPClient.h"
#include "timer.h"

#include <QObject>

#include <string>
#include <memory>

class TClient : public QObject
{
    Q_OBJECT

public:
    using handler_exception_t
        = std::function<void(std::exception_ptr, TClient*)>;
    static constexpr auto default_exception_handler
        = [](std::exception_ptr, TClient*) {};

    TClient(QObject* parent = nullptr);
    ~TClient();

    void SendMessage(
        const std::string& host, uint16_t port, const void* buffer, size_t size
    );

    void StartSendingMessage(
        uint32_t timeout,
        const std::string& host, uint16_t port, const void* buffer, size_t size,
        handler_exception_t hndl_except = default_exception_handler
    );

    void StopSendingMessage();

    bool IsSending() const;

private:
    ws2::TUDPClient _client;
    std::unique_ptr<wstd::timer> _timer;

signals:
    void StatusSendingTimerChanged(bool);
    void StatusSendingChanged(bool);

}; //class TClient
//-------------------------------------------------------------------

#endif // TCLIENT_H
