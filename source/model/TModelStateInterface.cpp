#include "TModelStateInterface.h"

#include "TClient.h"
#include "TServer.h"

TModelStateInterface::TModelStateInterface(
    TClient* client, TServer* server, QObject* parent)
    : QObject(parent), _client(client), _server(server)
{
    connect(
        client, SIGNAL(statusSendingTimerChanged(bool)),
        this, SIGNAL(statusSendingTimerChanged(bool))
    );
    connect(
        client, SIGNAL(statusSendingChanged(bool)),
        this, SIGNAL(statusSendingChanged(bool))
    );
    connect(
        server, SIGNAL(statusReceivingChanged(bool)),
        this, SIGNAL(statusReceivingChanged(bool))
    );
    connect(
        server, SIGNAL(storageDataChanged()),
        this, SIGNAL(storageDataChanged())
    );
    connect(
        server, SIGNAL(storageClear()),
        this, SIGNAL(storageClear())
    );
}//------------------------------------------------------------------


TModelStateInterface::~TModelStateInterface() {
}//------------------------------------------------------------------


bool TModelStateInterface::IsTimerSending() const {
    return _client->IsTimerSending();
}//------------------------------------------------------------------


bool TModelStateInterface::isReceiving() const {
    return _server->isReceiving();
}//------------------------------------------------------------------


size_t TModelStateInterface::storageSize() const {
    return _server->getStorage().size();
}//------------------------------------------------------------------


Package TModelStateInterface::storageItem(const size_t index) {
    return _server->getStorage().at(index);
}//------------------------------------------------------------------
