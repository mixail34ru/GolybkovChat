#include "TModelStateInterface.h"

#include "TClient.h"

TModelStateInterface::TModelStateInterface(const TClient* client, QObject* parent)
    : QObject(parent), _client(client)
{
    connect(
        client, SIGNAL(StatusSendingTimerChanged(bool)),
        this, SIGNAL(StatusSendingTimerChanged(bool))
    );
    connect(
        client, SIGNAL(StatusSendingChanged(bool)),
        this, SIGNAL(StatusSendingChanged(bool))
    );
}//------------------------------------------------------------------


TModelStateInterface::~TModelStateInterface() {
}//------------------------------------------------------------------


bool TModelStateInterface::IsSending() const {
    return _client->IsSending();
}//------------------------------------------------------------------
