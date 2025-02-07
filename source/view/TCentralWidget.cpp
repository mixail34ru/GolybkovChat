#include "TCentralWidget.h"

#include <QHBoxLayout>

TCentralWidget::TCentralWidget(TModelStateInterface* model, QWidget* parent)
    : QWidget(parent)
{
    /* Отправка пакета */

    _sender_wgt = new TSenderWidget(model, this);
    connect(
        _sender_wgt, &TSenderWidget::sendActivated,
        this, &TCentralWidget::sendActivated
    );
    connect(
        _sender_wgt, &TSenderWidget::sendTimerActivated,
        this, &TCentralWidget::sendTimerActivated
    );
    connect(
        _sender_wgt, &TSenderWidget::addPackageActivated,
        this, &TCentralWidget::addPackageActivated
    );
    connect(
        _sender_wgt, &TSenderWidget::showParcelEditActivated,
        this, &TCentralWidget::showParcelEditActivated
        );

    /* Приём пакета */

    _receiver_wgt = new TReceiverWidget(model, this);
    connect(
        _receiver_wgt, SIGNAL(receivePackageActivated(uint16_t, uint16_t)),
        this, SIGNAL(receivePackageActivated(uint16_t, uint16_t))
    );

    /* Настройка параметров центрального виджета */

    QHBoxLayout* horizontal_lt = new QHBoxLayout(this);
    horizontal_lt->addWidget(_sender_wgt, false);
    horizontal_lt->addWidget(_receiver_wgt, true);

    this->setLayout(horizontal_lt);
}//------------------------------------------------------------------


TCentralWidget::~TCentralWidget() {
}//------------------------------------------------------------------
