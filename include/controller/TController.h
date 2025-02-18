#ifndef TCONTROLLER_H
#define TCONTROLLER_H

<<<<<<< HEAD
=======
#include "TMainWindow.h"

#include "TClient.h"
#include "TServer.h"
#include "TModelStateInterface.h"

>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
#include "thread_pool.h"
#include <TPackageFormat.h>

#include <QApplication>

class TClient;
class TServer;
class TModelStateInterface;
class TView;

class TController : public QApplication
{
    Q_OBJECT

<<<<<<< HEAD
=======
    std::unique_ptr<wstd::thread_pool> _pool;

    TClient _client;
    TServer* _server;
    TModelStateInterface* _interface;

    std::unique_ptr<TMainWindow> _main_wnd;

>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
public:
    TController(int &argc, char **argv);
    ~TController();

<<<<<<< HEAD
private:
    std::unique_ptr<wstd::thread_pool> _pool;

    TClient* _client;
    TServer* _server;
    TModelStateInterface* _model;
    TView* _view;

    Package ViewInfoToPackageConverter(const ViewSendInfo& vinfo);
    void debugSendInfo(const ViewSendInfo& info) const;

private slots:
    void addSendPackage(ViewSendPackage pack);
    void delSendPackage(int index);
    void clearSendStorage() noexcept;

    void send_package(ViewSendInfo info);
    void send_timer_package(uint timeout, ViewSendInfo info);

    void startReceivePackage(uint16_t max_pack, uint16_t port);
    void clearReceiverStorage();


=======
private slots:
    void send_package(ViewSendInfo info);
    void send_timer_package(uint timeout, ViewSendInfo info);

    void startReceivePackage(uint16_t port);

private:
    Package ViewInfoToPackageConverter(const ViewSendInfo& vinfo);
    void debugSendInfo(const ViewSendInfo& info) const;
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

}; //class TController
//-------------------------------------------------------------------

#endif // TCONTROLLER_H
