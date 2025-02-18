#include "TCentralWidget.h"
#include "TSenderWidget.h"
#include "TReceiverWidget.h"

#include <QHBoxLayout>


TCentralWidget::TCentralWidget(TModelStateInterface* model, QWidget* parent)
    : QWidget(parent)
{
    /* Отправка пакета */

    _sender_wgt = new TSenderWidget(model, this);
    connect(
        _sender_wgt, &TSenderWidget::showParcelEditActivated,
        this, &TCentralWidget::showParcelEditActivated
    );
    connect(
        _sender_wgt, &TSenderWidget::addSendPackageActivated,
        this, &TCentralWidget::addSendPackageActivated
    );
    connect(
        _sender_wgt, &TSenderWidget::sendActivated,
        this, &TCentralWidget::sendActivated
    );
    connect(
        _sender_wgt, &TSenderWidget::sendTimerActivated,
        this, &TCentralWidget::sendTimerActivated
    );

    /* Приём пакета */

    _receiver_wgt = new TReceiverWidget(model, this);
    connect(
        _receiver_wgt, &TReceiverWidget::receivePackageActivated,
        this, &TCentralWidget::receivePackageActivated
    );
    connect(
        _receiver_wgt, &TReceiverWidget::clearReceiveStorageActivated,
        this, &TCentralWidget::clearReceiveStorageActivated
    );

    /* Настройка параметров центрального виджета */

    QHBoxLayout* horizontal_lt = new QHBoxLayout(this);
    horizontal_lt->addWidget(_sender_wgt, false);
    horizontal_lt->addWidget(_receiver_wgt, true);

    this->setLayout(horizontal_lt);
}//------------------------------------------------------------------


TCentralWidget::~TCentralWidget() {
}//------------------------------------------------------------------
