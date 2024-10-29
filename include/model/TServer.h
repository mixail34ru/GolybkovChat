#ifndef TSERVER_H
#define TSERVER_H

#include "TUDPServer.h"
#include "TSaveVecDataStorage.h"

#include <QObject>

#include <memory>

class TServer : public QObject
{
    Q_OBJECT

    TSaveVecDataStorage<Package> _storage;
    std::unique_ptr<ws2::TUDPServer> _udp_server;

public:
    using handler_exception_t
        = std::function<void(std::exception_ptr, TServer*)>;
    static constexpr auto default_exception_handler
        = [](std::exception_ptr, TServer*) {};

    TServer(QObject* parent = nullptr);
    ~TServer();

    void startReceiving(
        uint16_t port,
        handler_exception_t hndl_except = default_exception_handler
    );
    void stopReceiving();
    bool isReceiving() const;

    TSaveVecDataStorage<Package>& getStorage();

signals:
    void statusReceivingChanged(bool);
    void storageDataChanged();
    void storageClear();

}; //class TServer
//-------------------------------------------------------------------

#endif // TSERVER_H
