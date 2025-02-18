#ifndef TRECEIVERWIDGET_H
#define TRECEIVERWIDGET_H

#include "TRecvModeGroupBox.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class TModelStateInterface;

class TModelStateInterface;
class TRecvModeGroupBox;


class TReceiverWidget : public QWidget
{
    Q_OBJECT

    TRecvModeGroupBox* _mode_grp_bx;

public:
<<<<<<< HEAD
    explicit TReceiverWidget(
        TModelStateInterface* model, QWidget* parent = nullptr);
    ~TReceiverWidget();

signals:
    void receivePackageActivated(uint16_t max_pack, uint16_t port);
    void clearReceiveStorageActivated();

private:
    TRecvModeGroupBox* _mode_grp_bx;
=======
    TReceiverWidget(TModelStateInterface* model, QWidget* parent = nullptr);
    ~TReceiverWidget();

signals:
    void receivePackageActivated(uint16_t port);
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

}; //class TReceiverWidget
//-------------------------------------------------------------------

#endif // TRECEIVERWIDGET_H
