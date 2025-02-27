#ifndef TMAINWINDOW_H
#define TMAINWINDOW_H

#include "TPackageFormat.h"

#include <QMainWindow>

class TCentralWidget;
class TModelStateInterface;


class TMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TMainWindow(
        TModelStateInterface* model, QWidget *parent = nullptr);
    ~TMainWindow();

signals:
    void showParcelEditActivated();
    void addSendPackageActivated(ViewSendPackage pack);

    void sendActivated(NetAddress info);
    void sendTimerActivated(uint timeout, NetAddress info);

    void receiveActivated(uint16_t max_pack, uint16_t port);
    void clearReceiveStorageActivated();

private:
    TCentralWidget* _central_wgt;

}; //class TMainWindow
//-------------------------------------------------------------------

#endif // TMAINWINDOW_H
