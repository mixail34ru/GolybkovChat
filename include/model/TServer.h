#ifndef TSERVER_H
#define TSERVER_H

#include "TUDPServer.h"
#include "TPackageFormat.h"

#include "safe_ptr.h"
#include "TVecStorage.h"

#include <QObject>

#include <memory>

class TServer : public QObject
{
    Q_OBJECT

public:
    using handler_exception_t
        = std::function<void(std::exception_ptr, TServer*)>;
    static constexpr auto default_exception_handler
        = [](std::exception_ptr, TServer*) {};

    TServer(QObject* parent = nullptr);
    ~TServer();

    void startReceiving(
        uint16_t max_pack,
        uint16_t port,
        handler_exception_t hndl_except = default_exception_handler
    );
    void stopReceiving();
    bool isReceiving() const;

    wstd::safe_ptr<TVecStorage<ReceivePackage>>& getStorage();
    size_t parselSize() const;
    void storageClear() noexcept;

private:
    wstd::safe_ptr<TVecStorage<ReceivePackage>> _storage;
    std::unique_ptr<ws2::TUDPServer> _udp_server;

signals:
    void statusReceivingChanged(bool);
    void storageChanged();
    void storageCleared();

}; //class TServer
//-------------------------------------------------------------------

#endif // TSERVER_H
