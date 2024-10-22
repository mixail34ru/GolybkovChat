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

    _main_wnd = std::make_unique<TMainWindow>(new TModelStateInterface(&_client));
    connect(
        _main_wnd.get(), &TMainWindow::send_package_activated,
        this, &TController::send_package
    );
    connect(
        _main_wnd.get(), &TMainWindow::send_timer_package_activated,
        this, &TController::send_timer_package
    );

    _main_wnd->show();
}//------------------------------------------------------------------


TController::~TController() {
}//------------------------------------------------------------------


void TController::send_package(SendInfo info) {
    _client.SendMessage(
        info.address.ip,
        info.address.port,
        reinterpret_cast<void*>(&info.package),
        sizeof(info.package)
    );

    debugSendInfo(info);
}//------------------------------------------------------------------


void TController::send_timer_package(uint timeout, SendInfo info) {
    _pool->add_job([=, &info](){
        if (_client.IsSending()) {
            _client.StopSendingMessage();
        }
        else {
            _client.StartSendingMessage(
                timeout,
                info.address.ip,
                info.address.port,
                reinterpret_cast<void*>(&info.package),
                sizeof(info.package),
                ThreadExceptionHandler<TClient>(
                    _pool, [this](){ _client.StopSendingMessage(); }
                )
            );
        }
    });

    debugSendInfo(info);
}//------------------------------------------------------------------


void TController::debugSendInfo(const SendInfo& info) const {
    qDebug() << "SendInfo: "
             << "TypeData: " << info.package.type_data
             << "\tTypeSignal: " << info.package.type_signal
             << "\tID: " << info.package.id
             << "\tPayload.parameter: " << info.package.payload.parameter
             << "\tPayload.word: " << info.package.payload.word
             << "\tPayload.llword: " << info.package.payload.llword
             << "\tIP: " << info.address.ip
             << "\tPort: " << info.address.port;
}//------------------------------------------------------------------



