#include "TCentralWidget.h"

#include <QHBoxLayout>

TCentralWidget::TCentralWidget(TModelStateInterface* model, QWidget* parent)
    : QWidget(parent)
{
    /* Отправка пакета */

    _sender_wgt = new TSenderWidget(model, this);
    connect(
        _sender_wgt, &TSenderWidget::send_activated,
        this, &TCentralWidget::send_activated
    );
    connect(
        _sender_wgt, &TSenderWidget::send_timer_activated,
        this, &TCentralWidget::send_timer_activated
    );

    /* Приём пакета */

    _receiver_wgt = new TReceiverWidget(this);

    /* Настройка параметров центрального виджета */

    QHBoxLayout* horizontal_lt = new QHBoxLayout(this);
    horizontal_lt->addWidget(_sender_wgt);
    horizontal_lt->addWidget(_receiver_wgt);

    this->setLayout(horizontal_lt);
}//------------------------------------------------------------------


TCentralWidget::~TCentralWidget() {
}//------------------------------------------------------------------
