#ifndef TCONTROLLER_H
#define TCONTROLLER_H

#include "TMainWindow.h"

#include "TClient.h"
#include "TModelStateInterface.h"

#include "thread_pool.h"

#include <QApplication>

#include <memory>

class TController : public QApplication
{
    Q_OBJECT

    std::unique_ptr<wstd::thread_pool> _pool;

    TClient _client;
    TModelStateInterface* _interface;

    std::unique_ptr<TMainWindow> _main_wnd;

public:
    TController(int &argc, char **argv);
    ~TController();

private slots:
    void send_package(SendInfo info);
    void send_timer_package(uint timeout, SendInfo info);

private:
    void debugSendInfo(const SendInfo& info) const;

}; //class TController
//-------------------------------------------------------------------

#endif // TCONTROLLER_H
