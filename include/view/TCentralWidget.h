#ifndef TCENTRALWIDGET_H
#define TCENTRALWIDGET_H

#include "TPackageFormat.h"

#include "TSenderWidget.h"
#include "TReceiverWidget.h"

#include <QWidget>

class TModelStateInterface;

class TCentralWidget : public QWidget
{
    Q_OBJECT

    TSenderWidget* _sender_wgt;
    TReceiverWidget* _receiver_wgt;

public:
    TCentralWidget(TModelStateInterface* model, QWidget* parent = nullptr);
    ~TCentralWidget();

signals:
    void sendActivated(ViewSendInfo info);
    void sendTimerActivated(uint timeout, ViewSendInfo info);
    void receivePackageActivated(uint16_t port);

}; //class TCentralWidget
//-------------------------------------------------------------------

#endif // TCENTRALWIDGET_H
