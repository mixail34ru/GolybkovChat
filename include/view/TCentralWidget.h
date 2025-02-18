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
<<<<<<< HEAD
    void showParcelEditActivated();
    void addSendPackageActivated(ViewSendPackage pack);

    void sendActivated(ViewSendInfo info);
    void sendTimerActivated(uint timeout, ViewSendInfo info);

    void receivePackageActivated(uint16_t max_pack, uint16_t port);
    void clearReceiveStorageActivated();

private:
    TSenderWidget* _sender_wgt;
    TReceiverWidget* _receiver_wgt;
=======
    void sendActivated(ViewSendInfo info);
    void sendTimerActivated(uint timeout, ViewSendInfo info);
    void receivePackageActivated(uint16_t port);
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

}; //class TCentralWidget
//-------------------------------------------------------------------

#endif // TCENTRALWIDGET_H
