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
    void send_package_activated(SendInfo info);
    void send_timer_package_activated(uint timeout, SendInfo info);

}; //class TMainWindow
//-------------------------------------------------------------------

#endif // TMAINWINDOW_H
