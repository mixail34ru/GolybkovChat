#ifndef TRECEIVERWIDGET_H
#define TRECEIVERWIDGET_H

#include "TRecvModeGroupBox.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class TModelStateInterface;

class TReceiverWidget : public QWidget
{
    Q_OBJECT

    TRecvModeGroupBox* _mode_grp_bx;

public:
    TReceiverWidget(TModelStateInterface* model, QWidget* parent = nullptr);
    ~TReceiverWidget();

signals:
    void receivePackageActivated(uint16_t max_pack, uint16_t port);

}; //class TReceiverWidget
//-------------------------------------------------------------------

#endif // TRECEIVERWIDGET_H
