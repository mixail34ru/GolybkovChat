#ifndef TCLIENT_H
#define TCLIENT_H

#include "TUDPClient.h"
#include "timer.h"

#include "TPackageFormat.h"
#include "TVecStorage.h"

#include <QObject>

#include <string>
#include <memory>

#include <QVector>

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
        const std::string& host, uint16_t port,
        const void* buffer, size_t size
    );

    void StartSendingMessage(
        uint32_t timeout,
        const std::string& host, uint16_t port,
        const void* buffer, size_t size,
        handler_exception_t hndl_except = default_exception_handler
    );

    void StopSendingMessage();
    bool IsTimerSending() const;

<<<<<<< HEAD
    // const TVecStorage<ViewSendPackage>& getStorage() const noexcept;
    // size_t sizeStorage() const noexcept;
    // ViewSendPackage getItemStorage(const size_t& index);
    // void addPackToStorage(ViewSendPackage pack);
    // void erasePackFromStorage(int index);
    // void clearStorage() noexcept;

    const QVector<ViewSendPackage>& getStorage() const noexcept;
    void appendToStorage(const ViewSendPackage& value);
    void removeFromStorage(int i, int count = 1);
    void clearStorage();
=======
    bool IsTimerSending() const;
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

private:
    QVector<ViewSendPackage> _storage;

    //TVecStorage<ViewSendPackage> _storage;
    ws2::TUDPClient _client;
    std::unique_ptr<wstd::timer> _timer;

signals:
    void statusSendingTimerChanged(bool);
    void statusSendingChanged(bool);
<<<<<<< HEAD

    //void storageChanged();
    //void storageCleared();

    void storageInserted(int, int);
    void storageErased(int, int);
    void storageCleared();
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

}; //class TClient
//-------------------------------------------------------------------

#endif // TCLIENT_H
