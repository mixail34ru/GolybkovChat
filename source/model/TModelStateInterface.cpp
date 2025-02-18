#include "TModelStateInterface.h"

#include "TClient.h"
#include "TServer.h"

TModelStateInterface::TModelStateInterface(
    TClient* client, TServer* server, QObject* parent)
    : QObject(parent), _client(client), _server(server)
{
    /* client */

    // connect(
    //     client, &TClient::storageCleared,
    //     this, &TModelStateInterface::sendStorageCleared
    //     );
    // connect(
    //     client, &TClient::storageChanged,
    //     this, &TModelStateInterface::sendStorageChanged
    //     );

    connect(client, &TClient::storageInserted,
            this, &TModelStateInterface::sendStorageInserted);

    connect(client, &TClient::storageErased,
            this, &TModelStateInterface::sendStorageErased);

    connect(client, &TClient::storageCleared,
            this, &TModelStateInterface::sendStorageCleared);

    connect(
        client, SIGNAL(statusSendingTimerChanged(bool)),
        this, SIGNAL(statusSendingTimerChanged(bool))
    );
    connect(
        client, SIGNAL(statusSendingChanged(bool)),
        this, SIGNAL(statusSendingChanged(bool))
    );
<<<<<<< HEAD

    /* server */

=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    connect(
        server, SIGNAL(statusReceivingChanged(bool)),
        this, SIGNAL(statusReceivingChanged(bool))
    );
    connect(
<<<<<<< HEAD
        server, SIGNAL(storageChanged()),
        this, SIGNAL(recvStorageChanged())
    );
    connect(
        server, SIGNAL(storageCleared()),
        this, SIGNAL(recvStorageCleared())
=======
        server, SIGNAL(storageDataChanged()),
        this, SIGNAL(storageDataChanged())
    );
    connect(
        server, SIGNAL(storageClear()),
        this, SIGNAL(storageClear())
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    );
}//------------------------------------------------------------------


TModelStateInterface::~TModelStateInterface() {
}//------------------------------------------------------------------


<<<<<<< HEAD
const QVector<ViewSendPackage>&
TModelStateInterface::getSendStorage() const noexcept {
    return _client->getStorage();
}//------------------------------------------------------------------


// const TVecStorage<ViewSendPackage>&
// TModelStateInterface::getSendStorage() const noexcept {
//     return _client->getStorage();
// }//------------------------------------------------------------------


// size_t TModelStateInterface::sizeSendStorage() const noexcept {
//     return  _client->sizeStorage();
// }//------------------------------------------------------------------


// void TModelStateInterface::erasePackFromStorage(int index) {
//     _client->erasePackFromStorage(index);
// }//------------------------------------------------------------------


// ViewSendPackage TModelStateInterface::itemSendStorage(const size_t index) {
//     return _client->getItemStorage(index);
// }//------------------------------------------------------------------


=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
bool TModelStateInterface::IsTimerSending() const {
    return _client->IsTimerSending();
}//------------------------------------------------------------------


bool TModelStateInterface::isReceiving() const {
    return _server->isReceiving();
}//------------------------------------------------------------------


size_t TModelStateInterface::storageSize() const {
<<<<<<< HEAD
    int full_size = 0;
    for( int i = 0; i < _server->getStorage()->size(); i++)
    {
        full_size +=  _server->getStorage()->at(i).parsel.size();
    }
    return full_size;
=======
    return _server->getStorage().size();
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
}//------------------------------------------------------------------


Package TModelStateInterface::storageItem(const size_t index) {
<<<<<<< HEAD
        int recvpack_size = _server->getStorage()->size();
        int min_index = 0;
        int max_index = 0;
        for (int i = 0; i < recvpack_size; i++){
            max_index = min_index + _server->getStorage()->at(i).parsel.size();
            if (index < max_index){
                return _server->getStorage()->at(i).parsel.at(index - min_index);
            }
            else
                min_index += _server->getStorage()->at(i).parsel.size();
        }
}//------------------------------------------------------------------


ReceivePackage TModelStateInterface::timeItem(const size_t index){
        int recvpack_size = _server->getStorage()->size();
        int min_index = 0;
        int max_index = 0;
        for (int i = 0; i < recvpack_size; i++){
            max_index = min_index + _server->getStorage()->at(i).parsel.size();
            if (index < max_index)
                return _server->getStorage()->at(i);
            else
                min_index += _server->getStorage()->at(i).parsel.size();
        }
=======
    return _server->getStorage().at(index);
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
}//------------------------------------------------------------------
