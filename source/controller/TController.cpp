#include "TController.h"

#include <QDebug>

#include <functional>

template<typename Owner>
auto ThreadExceptionHandler(std::unique_ptr<wstd::thread_pool>& catcher, std::function<void()> handler) {
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
}//----------------------------------------------------------------------------


TController::TController(int &argc, char **argv)
    : QApplication(argc, argv)
{
    _pool = std::make_unique<wstd::thread_pool>(2);

    _server = new TServer(this);


    _main_wnd = std::make_unique<TMainWindow>(new TModelStateInterface(&_client, _server));
    connect(
        _main_wnd.get(), &TMainWindow::sendActivated,
        this, &TController::send_package
    );
    connect(
        _main_wnd.get(), &TMainWindow::sendTimerActivated,
        this, &TController::send_timer_package
    );
    connect(
        _main_wnd.get(), &TMainWindow::receiveActivated,
        this, &TController::startReceivePackage
    );

    _main_wnd->show();
    auto temp = new QWidget();
    temp->show();
}//------------------------------------------------------------------


TController::~TController() {
}//------------------------------------------------------------------


void TController::send_package(ViewSendInfo info) {
    Package package = ViewInfoToPackageConverter(info);

    _client.SendMessage(
        info.address.ip,
        info.address.port,
        reinterpret_cast<void*>(&package),
        sizeof(package)
    );

    debugSendInfo(info);
}//------------------------------------------------------------------


void TController::send_timer_package(uint timeout, ViewSendInfo info) {
    _pool->add_job([=, &info](){
        if (_client.IsTimerSending()) {
            _client.StopSendingMessage();
        }
        else {
            Package package = ViewInfoToPackageConverter(info);
            _client.StartSendingMessage(
                timeout,
                info.address.ip,
                info.address.port,
                reinterpret_cast<void*>(&package),
                sizeof(package),
                ThreadExceptionHandler<TClient>(
                    _pool, [this](){ _client.StopSendingMessage(); }
                )
            );
        }
    });

    debugSendInfo(info);
}//------------------------------------------------------------------


void TController::startReceivePackage(uint16_t port) {
    if (_server->isReceiving()) {
        _server->stopReceiving();
    }
    else {
        _server->startReceiving(
            port,
            ThreadExceptionHandler<TServer>(
                _pool, [this]() { _server->stopReceiving(); }
            )
        );
    }
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
             << "\tPayload.llword: " << info.package.payload.llword
             << "\tIP: " << info.address.ip
             << "\tPort: " << info.address.port;
}//------------------------------------------------------------------



