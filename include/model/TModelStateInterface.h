#ifndef TMODELSTATEINTERFACE_H
#define TMODELSTATEINTERFACE_H

#include <QObject>

class TClient;

class TModelStateInterface : public QObject
{
    Q_OBJECT

    const TClient* _client;

public:
    TModelStateInterface(const TClient* client, QObject* parent = nullptr);
    ~TModelStateInterface();

    bool IsSending() const;

signals:
    void StatusSendingTimerChanged(bool);
    void StatusSendingChanged(bool);

}; //class TModelStateInterface
//-------------------------------------------------------------------

#endif // TMODELSTATEINTERFACE_H
