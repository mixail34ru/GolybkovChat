#ifndef TCONTROLLER_H
#define TCONTROLLER_H

#include "thread_pool.h"
#include <TPackageFormat.h>
#include <TVecStorage.h>

#include <QApplication>

class TClient;
class TServer;
class TModelStateInterface;
class TView;

class TController : public QApplication
{
    Q_OBJECT

public:
    TController(int &argc, char **argv);
    ~TController();

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
    void send_parsel(NetAddress info);
    void send_timer_parsel(uint timeout, NetAddress info);

    void startReceivePackage(uint16_t max_pack, uint16_t port);
    void clearReceiverStorage();



}; //class TController
//-------------------------------------------------------------------

#endif // TCONTROLLER_H
