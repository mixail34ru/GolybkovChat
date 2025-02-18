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
<<<<<<< HEAD
    void showParcelEditActivated();
    void addSendPackageActivated(ViewSendPackage pack);

    void sendActivated(ViewSendInfo info);
    void sendTimerActivated(uint timeout, ViewSendInfo info);

    void receiveActivated(uint16_t max_pack, uint16_t port);
    void clearReceiveStorageActivated();

private:
    TCentralWidget* _central_wgt;
=======
    void sendActivated(ViewSendInfo info);
    void sendTimerActivated(uint timeout, ViewSendInfo info);
    void receiveActivated(uint16_t port);
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

}; //class TMainWindow
//-------------------------------------------------------------------

#endif // TMAINWINDOW_H
