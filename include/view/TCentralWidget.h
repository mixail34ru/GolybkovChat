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
    void send_activated(SendInfo info);
    void send_timer_activated(uint timeout, SendInfo info);

}; //class TCentralWidget
//-------------------------------------------------------------------

#endif // TCENTRALWIDGET_H
