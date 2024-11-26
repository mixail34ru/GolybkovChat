#include "TServer.h"

#include <QDebug>

TServer::TServer(QObject* parent) : QObject(parent) {
    _storage.dataChanged = [this]() { emit storageDataChanged(); };
    _storage.dataCleared = [this]() { emit storageClear(); };
}//------------------------------------------------------------------


TServer::~TServer() {
}//------------------------------------------------------------------


void TServer::startReceiving(uint16_t max_pack, uint16_t port, handler_exception_t hndl_except) {
    try {
        if (!_udp_server) {
            _storage.clear();
            std::shared_ptr<Package> pack(new Package());

            _udp_server = std::make_unique<ws2::TUDPServer>(
                port,
                sizeof(Package),
                [this, max_pack, pack](
                    ws2::DataBuffer buff,
                    ws2::SocketAddr_in& addr,
                    ws2::SockLen_t addr_len,
                    ws2::TUDPServer* server)
                {
                    memcpy(pack.get(), buff.data(), sizeof(Package));
                    ReceivePackage recvpack {
                        std::chrono::high_resolution_clock::now(),
                        *(pack.get())
                    };
                    _storage.push_back(recvpack);

                    qDebug() << "ReceiveInfo: "
                             << "TypeData: " << pack->type_data
                             << "\tTypeSignal: " << pack->type_signal
                             << "\tID: " << pack->id
                             << "\tPayload.parameter: " << pack->payload.parameter
                             << "\tMax number of packages: " << max_pack;
                },
                [this, hndl_except](std::exception_ptr eptr, ws2::TUDPServer* server) {
                    hndl_except(eptr, this);
                }
            );
        }
        emit statusReceivingChanged(true);
    }
    catch (...) {
        // do something
    }
}//------------------------------------------------------------------


void TServer::stopReceiving() {
    if (_udp_server) _udp_server.reset();
    emit statusReceivingChanged(false);
}//------------------------------------------------------------------


bool TServer::isReceiving() const {
    return (_udp_server.get() != nullptr ? true : false);
}//------------------------------------------------------------------


TSaveVecDataStorage<ReceivePackage>& TServer::getStorage(){
    return _storage;
}//------------------------------------------------------------------
