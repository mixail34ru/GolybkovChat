#ifndef TCONTROLLER_H
#define TCONTROLLER_H

//#include "TMainWindow.h"
#include "TView.h"

#include "TClient.h"
#include "TServer.h"
#include "TModelStateInterface.h"

#include "thread_pool.h"

#include <QApplication>

#include <memory>

class TController : public QApplication
{
    Q_OBJECT

    std::unique_ptr<wstd::thread_pool> _pool;

    TClient _client;
    TServer* _server;
    TModelStateInterface* _interface;

    std::unique_ptr<TView> _view;

public:
    TController(int &argc, char **argv);
    ~TController();

private slots:
    void send_package(ViewSendInfo info);
    void send_timer_package(uint timeout, ViewSendInfo info);

    void startReceivePackage(uint16_t max_pack, uint16_t port);

private:
    Package ViewInfoToPackageConverter(const ViewSendInfo& vinfo);
    void debugSendInfo(const ViewSendInfo& info) const;

}; //class TController
//-------------------------------------------------------------------

#endif // TCONTROLLER_H
