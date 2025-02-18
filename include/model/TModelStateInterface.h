#ifndef TMODELSTATEINTERFACE_H
#define TMODELSTATEINTERFACE_H

#include <TPackageFormat.h>
#include <TVecStorage.h>
#include <QObject>
#include <QVector>

class TClient;
class TServer;

class TModelStateInterface : public QObject
{
    Q_OBJECT

    TClient* _client;
    TServer* _server;

public:
    explicit TModelStateInterface(
        TClient* client,
        TServer* server,
        QObject* parent = nullptr
    );
    virtual ~TModelStateInterface();

    //const TVecStorage<ViewSendPackage>& getSendStorage() const noexcept;

    //size_t sizeSendStorage() const noexcept;
    //void erasePackFromStorage(int index);
    //ViewSendPackage itemSendStorage(const size_t index);


    const QVector<ViewSendPackage>& getSendStorage() const noexcept;


    bool IsTimerSending() const;
    bool isReceiving() const;

    size_t storageSize() const;
    Package storageItem(const size_t index);
    ReceivePackage timeItem(const size_t index);

signals:
    void sendStorageInserted(int, int);
    void sendStorageErased(int, int);
    void sendStorageCleared();

    //void sendStorageChanged();
    //void sendStorageCleared();

    void statusSendingTimerChanged(bool);
    void statusSendingChanged(bool);

    void statusReceivingChanged(bool);
    void recvStorageChanged();
    void recvStorageCleared();
    //void tableCleared();

}; //class TModelStateInterface
//-------------------------------------------------------------------

#endif // TMODELSTATEINTERFACE_H
