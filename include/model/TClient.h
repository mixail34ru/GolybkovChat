#ifndef TCLIENT_H
#define TCLIENT_H

#include "TUDPClient.h"
#include "timer.h"

#include "TPackageFormat.h"

#include <QObject>
#include <QVector>

#include <string>
#include <memory>


class TClient final : public QObject
{
    Q_OBJECT

public:
    using handler_exception_t
        = std::function<void(std::exception_ptr, TClient*)>;
    static constexpr auto default_exception_handler
        = [](std::exception_ptr, TClient*) {};

    explicit TClient(QObject* parent = nullptr);
    ~TClient();

    void SendMessage(
        const std::string& host, uint16_t port,
        const void* buffer, size_t size
    );

    void StartSendingMessage(
        uint32_t timeout,
        const std::string& host, uint16_t port,
        const void* buffer, size_t size,
        handler_exception_t hndl_except = default_exception_handler
    );

    void SendParsel(NetAddress info);

    void SendTimerParsel(
        uint32_t timeout,
        NetAddress info,
        handler_exception_t hndl_except
    );

    void StopSendingMessage();
    bool IsTimerSending() const;

    const QVector<ViewSendPackage>& getStorage() const noexcept;
    void appendToStorage(const ViewSendPackage& value);
    void removeFromStorage(int i, int count = 1);
    void clearStorage();

private:
    QVector<ViewSendPackage> _storage;
    ws2::TUDPClient _client;
    std::unique_ptr<wstd::timer> _timer;

    void checkPackages() const;
    Package ViewSendPackageToPackageConverter(
        const ViewSendPackage& info) const noexcept;

signals:
    void statusSendingTimerChanged(bool);
    void statusSendingChanged(bool);

    void storageInserted(int, int);
    void storageErased(int, int);
    void storageCleared();

}; //class TClient
//-------------------------------------------------------------------

#endif // TCLIENT_H
