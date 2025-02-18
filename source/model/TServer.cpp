#include "TServer.h"

#include <QDebug>

TServer::TServer(QObject* parent) : QObject(parent) {
<<<<<<< HEAD
    _storage->dataChanged = [this]() { emit storageChanged(); };
    _storage->dataCleared = [this]() { emit storageCleared(); };
=======
    _storage.dataChanged = [this]() { emit storageDataChanged(); };
    _storage.dataCleared = [this]() { emit storageClear(); };
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
}//------------------------------------------------------------------


TServer::~TServer() {
}//------------------------------------------------------------------


<<<<<<< HEAD
void TServer::startReceiving(
    uint16_t max_pack, uint16_t port, handler_exception_t hndl_except)
{
    try {
        if (!_udp_server) {
            _storage->clear();
            size_t parsel_size = sizeof(Package)*max_pack;

            std::shared_ptr<Package[]> pack {std::make_unique<Package[]>(max_pack)};

            _udp_server = std::make_unique<ws2::TUDPServer>(
                port,
                parsel_size,
                [this, max_pack, pack, parsel_size](
=======
void TServer::startReceiving(uint16_t port, handler_exception_t hndl_except) {
    try {
        if (!_udp_server) {
            _storage.clear();
            std::shared_ptr<Package> pack(new Package());

            _udp_server = std::make_unique<ws2::TUDPServer>(
                port,
                sizeof(Package),
                [this, pack](
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
                    ws2::DataBuffer buff,
                    ws2::SocketAddr_in& addr,
                    ws2::SockLen_t addr_len,
                    ws2::TUDPServer* server)
                {
<<<<<<< HEAD
                    memcpy(pack.get(), buff.data(), parsel_size);

                    std::vector<Package> vec;

                    for (int i = 0; i < parsel_size; i += sizeof(Package))
                    {
                        Package pack_vec;
                        memcpy(&pack_vec, buff.data()+i, sizeof(Package));
                        int8_t buf = pack_vec.type_data;
                        if (buf == -1 || buf == -3 || buf == -4 || buf == 1 || buf == 3 || buf == 4)
                        {
                            vec.push_back(pack_vec);
                        }
                        else break;
                    }

                    if (!(vec.empty())){
                        ReceivePackage recvpack {
                            std::chrono::high_resolution_clock::now(),
                            vec
                        };
                    _storage->push_back(recvpack);
                    }

                    for (auto& it : vec)
                    {
                        qDebug() << "ReceiveInfo: "
                                 << "TypeData: " << it.type_data  //pack[i].type_data
                                 << "\tTypeSignal: " << it.type_signal
                                 << "\tID: " << it.id
                                 << "\tPayload.parameter: " << it.payload.parameter
                                 << "\tMax number of packages: " << max_pack;
                    }

=======
                    memcpy(pack.get(), buff.data(), sizeof(Package));
                    _storage.push_back(*(pack.get()));

                    qDebug() << "ReceiveInfo: "
                             << "TypeData: " << pack->type_data
                             << "\tTypeSignal: " << pack->type_signal
                             << "\tID: " << pack->id
                             << "\tPayload.parameter: " << pack->payload.parameter;
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
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


<<<<<<< HEAD
wstd::safe_ptr<TVecStorage<ReceivePackage>>& TServer::getStorage() {
    return _storage;
}//------------------------------------------------------------------


size_t TServer::parselSize() const {
    return ReceivePackage().parsel.size();
}//------------------------------------------------------------------


void TServer::storageClear() noexcept {
    _storage->clear();
}//------------------------------------------------------------------
=======
TSaveVecDataStorage<Package>& TServer::getStorage(){
    return _storage;
}//------------------------------------------------------------------
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
