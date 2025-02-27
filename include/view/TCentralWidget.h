#ifndef TCENTRALWIDGET_H
#define TCENTRALWIDGET_H

#include "TPackageFormat.h"

#include <QWidget>

class TModelStateInterface;
class TSenderWidget;
class TReceiverWidget;


class TCentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TCentralWidget(
        TModelStateInterface* model, QWidget* parent = nullptr);
    ~TCentralWidget();

signals:
    void showParcelEditActivated();
    void addSendPackageActivated(ViewSendPackage pack);

    void sendActivated(/*ViewSendInfo*/NetAddress info);
    void sendTimerActivated(uint timeout, /*ViewSendInfo*/NetAddress info);

    void receivePackageActivated(uint16_t max_pack, uint16_t port);
    void clearReceiveStorageActivated();

private:
    TSenderWidget* _sender_wgt;
    TReceiverWidget* _receiver_wgt;

}; //class TCentralWidget
//-------------------------------------------------------------------

#endif // TCENTRALWIDGET_H
