#ifndef TMODELSTATEINTERFACE_H
#define TMODELSTATEINTERFACE_H

#include <TPackageFormat.h>
#include <QObject>

#include "TSaveVecDataStorage.h"

class TClient;
class TServer;

class TModelStateInterface : public QObject
{
    Q_OBJECT

    TClient* _client;
    TServer* _server;

public:
    TModelStateInterface(
        TClient* client,
        TServer* server,
        QObject* parent = nullptr
    );
    ~TModelStateInterface();

    bool IsTimerSending() const;
    bool isReceiving() const;

    size_t storageSize() const;
    Package storageItem(const size_t index);
    ReceivePackage timeItem(const size_t index);

signals:
    void statusSendingTimerChanged(bool);
    void statusSendingChanged(bool);

    void statusReceivingChanged(bool);
    void storageDataChanged();
    void storageClear();
    void tableClear();

}; //class TModelStateInterface
//-------------------------------------------------------------------

#endif // TMODELSTATEINTERFACE_H
