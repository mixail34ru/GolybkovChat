#ifndef TMAINWINDOW_H
#define TMAINWINDOW_H

#include "TCentralWidget.h"

#include <QMainWindow>

class TModelStateInterface;

class TMainWindow : public QMainWindow
{
    Q_OBJECT

    TCentralWidget* _central_wgt;

public:
    TMainWindow(TModelStateInterface* model, QWidget *parent = nullptr);
    ~TMainWindow();

signals:
    void sendActivated(ViewSendInfo info);
    void sendTimerActivated(uint timeout, ViewSendInfo info);
    void receiveActivated(uint16_t port);

}; //class TMainWindow
//-------------------------------------------------------------------

#endif // TMAINWINDOW_H
