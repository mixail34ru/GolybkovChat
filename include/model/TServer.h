#ifndef TSERVER_H
#define TSERVER_H

#include "TUDPServer.h"
<<<<<<< HEAD
#include "TPackageFormat.h"

#include "safe_ptr.h"
#include "TVecStorage.h"
=======
#include "TSaveVecDataStorage.h"
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

#include <QObject>

#include <memory>

class TServer : public QObject
{
    Q_OBJECT

<<<<<<< HEAD
=======
    TSaveVecDataStorage<Package> _storage;
    std::unique_ptr<ws2::TUDPServer> _udp_server;

>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
public:
    using handler_exception_t
        = std::function<void(std::exception_ptr, TServer*)>;
    static constexpr auto default_exception_handler
        = [](std::exception_ptr, TServer*) {};

    TServer(QObject* parent = nullptr);
    ~TServer();

    void startReceiving(
<<<<<<< HEAD
        uint16_t max_pack,
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
        uint16_t port,
        handler_exception_t hndl_except = default_exception_handler
    );
    void stopReceiving();
    bool isReceiving() const;

<<<<<<< HEAD
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
=======
    TSaveVecDataStorage<Package>& getStorage();

signals:
    void statusReceivingChanged(bool);
    void storageDataChanged();
    void storageClear();
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

}; //class TServer
//-------------------------------------------------------------------

#endif // TSERVER_H
