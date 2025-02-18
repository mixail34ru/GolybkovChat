#ifndef TMODELSTATEINTERFACE_H
#define TMODELSTATEINTERFACE_H

<<<<<<< HEAD
#include <TPackageFormat.h>
#include <TVecStorage.h>
=======
//#include "TServer.h"
#include <TPackageFormat.h>
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
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
<<<<<<< HEAD
    explicit TModelStateInterface(
=======
    TModelStateInterface(
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
        TClient* client,
        TServer* server,
        QObject* parent = nullptr
    );
<<<<<<< HEAD
    virtual ~TModelStateInterface();

    //const TVecStorage<ViewSendPackage>& getSendStorage() const noexcept;

    //size_t sizeSendStorage() const noexcept;
    //void erasePackFromStorage(int index);
    //ViewSendPackage itemSendStorage(const size_t index);


    const QVector<ViewSendPackage>& getSendStorage() const noexcept;


=======
    ~TModelStateInterface();

>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    bool IsTimerSending() const;
    bool isReceiving() const;

    size_t storageSize() const;
    Package storageItem(const size_t index);
<<<<<<< HEAD
    ReceivePackage timeItem(const size_t index);

signals:
    void sendStorageInserted(int, int);
    void sendStorageErased(int, int);
    void sendStorageCleared();

    //void sendStorageChanged();
    //void sendStorageCleared();

=======

signals:
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    void statusSendingTimerChanged(bool);
    void statusSendingChanged(bool);

    void statusReceivingChanged(bool);
<<<<<<< HEAD
    void recvStorageChanged();
    void recvStorageCleared();
    //void tableCleared();
=======
    void storageDataChanged();
    void storageClear();
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

}; //class TModelStateInterface
//-------------------------------------------------------------------

#endif // TMODELSTATEINTERFACE_H
