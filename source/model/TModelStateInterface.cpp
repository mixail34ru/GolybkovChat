#include "TModelStateInterface.h"

#include "TClient.h"
#include "TServer.h"
#include "TSaveVecDataStorage.h"

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

    connect(
        this, SIGNAL(tableClear()),
        server, SLOT(tableClear())
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
    int full_size = 0;
    for( int i = 0; i < _server->getStorage().size(); i++)
    {
        full_size +=  _server->getStorage().at(i).parsel.size();
    }
    return full_size;
}//------------------------------------------------------------------


Package TModelStateInterface::storageItem(const size_t index) {
        int recvpack_size = _server->getStorage().size();
        int min_index = 0;
        int max_index = 0;
        for (int i = 0; i < recvpack_size; i++){
            max_index = min_index + _server->getStorage().at(i).parsel.size();
            if (index < max_index){
                return _server->getStorage().at(i).parsel.at(index - min_index);
            }
            else
                min_index += _server->getStorage().at(i).parsel.size();
        }
}//------------------------------------------------------------------


ReceivePackage TModelStateInterface::timeItem(const size_t index){
        int recvpack_size = _server->getStorage().size();
        int min_index = 0;
        int max_index = 0;
        for (int i = 0; i < recvpack_size; i++){
            max_index = min_index + _server->getStorage().at(i).parsel.size();
            if (index < max_index)
                return _server->getStorage().at(i);
            else
                min_index += _server->getStorage().at(i).parsel.size();
        }
}//------------------------------------------------------------------
