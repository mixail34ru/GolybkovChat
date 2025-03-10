#include "TController.h"
#include "TView.h"
#include "TClient.h"
#include "TServer.h"
#include "TModelStateInterface.h"

#include <QDebug>

#include <functional>

template<typename Owner>
auto ThreadExceptionHandler(
    std::unique_ptr<wstd::thread_pool>& catcher,
    std::function<void()> handler)
{
    return [&catcher, handler](std::exception_ptr eptr, Owner* owner) {
        catcher->add_job(
            [=]() {
                try {
                    if (eptr) { std::rethrow_exception(eptr); }
                }
                catch (const std::exception& e) {
                    try {
                        qDebug() << e.what() << "thread_exception";
                        handler();
                    }
                    catch (...) {}
                }
            }
        );
    };
}//------------------------------------------------------------------


TController::TController(int &argc, char **argv)
    : QApplication(argc, argv)
{
    _pool = std::make_unique<wstd::thread_pool>(2);

    _client = new TClient(this);
    _server = new TServer(this);
    _model = new TModelStateInterface(_client, _server, this);

    _view = new TView(_model, this);
    connect(
        _view, &TView::addSendPackageActivated,
        this, &TController::addSendPackage
    );
    connect(
        _view, &TView::delSendPackageActivated,
        this, &TController::delSendPackage
    );
    connect(
        _view, &TView::clearSendStorageActivated,
        this, &TController::clearSendStorage
    );
    connect(
        _view, &TView::sendActivated,
        this, &TController::send_parsel
    );
    connect(
        _view, &TView::sendTimerActivated,
        this, &TController::send_timer_parsel
    );
    connect(
        _view, &TView::receiveActivated,
        this, &TController::startReceivePackage
    );
    connect(
        _view, &TView::clearReceiveStorageActivated,
        this, &TController::clearReceiverStorage
    );


    _view->run();
}//------------------------------------------------------------------


TController::~TController() {
}//------------------------------------------------------------------


void TController::addSendPackage(ViewSendPackage pack) {
    _client->appendToStorage(pack);
    //_client->addPackToStorage(pack);
}//------------------------------------------------------------------


void TController::delSendPackage(int index) {
    _client->removeFromStorage(index);
    //_client->erasePackFromStorage(index);
}//------------------------------------------------------------------


void TController::clearSendStorage() noexcept {
    _client->clearStorage();
}//------------------------------------------------------------------


void TController::send_package(ViewSendInfo info) {
    //Package package = ViewInfoToPackageConverter(info);
    std::vector<Package> vec_pack;
    for(int i = 0; i < info.count; i++){
        vec_pack.push_back(ViewInfoToPackageConverter(info));
    }

    _client->SendMessage(
        info.address.ip,
        info.address.port,
        reinterpret_cast<void*>(vec_pack.data()), //(&package),
        sizeof(Package)*vec_pack.size()
    );

    debugSendInfo(info);
}//------------------------------------------------------------------


void TController::send_parsel(NetAddress info)
{
    _client->SendParsel(info);
}

void TController::send_timer_parsel(uint timeout, NetAddress info)
{
    _pool->add_job([=, &info](){
        if (_client->IsTimerSending()) {
            _client->StopSendingMessage();
        }
        else{
            _client->SendTimerParsel(timeout, info,
                ThreadExceptionHandler<TClient>(
                    _pool, [this](){ _client->StopSendingMessage(); }
                )
            );
        }
    });
}


void TController::send_timer_package(uint timeout, ViewSendInfo info) {
    _pool->add_job([=, &info](){
        if (_client->IsTimerSending()) {
            _client->StopSendingMessage();
        }
        else {
             std::vector<Package> vec_pack;
             for(int i = 0; i < info.count; i++){
                 vec_pack.push_back(ViewInfoToPackageConverter(info));
             }
           // Package package = ViewInfoToPackageConverter(info);
            _client->StartSendingMessage(
                timeout,
                info.address.ip,
                info.address.port,
                reinterpret_cast<void*>(vec_pack.data()),   //(&package),
                sizeof(Package)*vec_pack.size(),
                ThreadExceptionHandler<TClient>(
                    _pool, [this](){ _client->StopSendingMessage(); }
                )
            );
        }
    });

    debugSendInfo(info);
}//------------------------------------------------------------------



void TController::startReceivePackage(uint16_t max_pack, uint16_t port) {
    if (_server->isReceiving()) {
        _server->stopReceiving();
    }
    else {
        _server->startReceiving(
            max_pack,
            port,
            ThreadExceptionHandler<TServer>(
                _pool, [this]() { _server->stopReceiving(); }
            )
        );
    }
}//------------------------------------------------------------------


void TController::clearReceiverStorage() {
    _server->storageClear();
}//------------------------------------------------------------------


Package TController::ViewInfoToPackageConverter(const ViewSendInfo& vinfo) {
    return Package {
        static_cast<int8_t>(vinfo.package.type_data),
        static_cast<int8_t>(vinfo.package.type_signal),
        vinfo.package.id,
        vinfo.package.payload.parameter

    };
}//------------------------------------------------------------------


void TController::debugSendInfo(const ViewSendInfo& info) const {
    qDebug() << "SendInfo: "
             << "TypeData: " << static_cast<int8_t>(info.package.type_data)
             << "\tTypeSignal: " << static_cast<int8_t>(info.package.type_signal)
             << "\tID: " << info.package.id
             << "\tPayload.parameter: " << info.package.payload.parameter
             << "\tPayload.word: " << info.package.payload.word
             << "\tPayload.llword: " <<info.package.payload.llword
             << "\tIP: " << info.address.ip
             << "\tPort: " << info.address.port;
}//------------------------------------------------------------------

/*
    for (auto& it : info.parsel)
    {
    qDebug() << "SendInfo: "
                 << "TypeData: " << static_cast<int8_t>(it.type_data) //(info.package.type_data)
             << "\tTypeSignal: " << static_cast<int8_t>(it.type_signal)  //(info.package.type_signal)
             << "\tID: " <<  (it.id) //info.package.id
             << "\tPayload.parameter: " << (it.payload.parameter)  //info.package.payload.parameter
             << "\tPayload.word: " << (it.payload.word) //info.package.payload.word
             << "\tPayload.llword: " << (it.payload.llword) //info.package.payload.llword
             << "\tIP: " << info.address.ip
             << "\tPort: " << info.address.port;
    }*/


