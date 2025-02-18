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
<<<<<<< HEAD
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
=======
        _sender_wgt, &TSenderWidget::sendActivated,
        this, &TCentralWidget::sendActivated
    );
    connect(
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
        _sender_wgt, &TSenderWidget::sendTimerActivated,
        this, &TCentralWidget::sendTimerActivated
    );

    /* Приём пакета */

    _receiver_wgt = new TReceiverWidget(model, this);
    connect(
<<<<<<< HEAD
        _receiver_wgt, &TReceiverWidget::receivePackageActivated,
        this, &TCentralWidget::receivePackageActivated
    );
    connect(
        _receiver_wgt, &TReceiverWidget::clearReceiveStorageActivated,
        this, &TCentralWidget::clearReceiveStorageActivated
=======
        _receiver_wgt, SIGNAL(receivePackageActivated(uint16_t)),
        this, SIGNAL(receivePackageActivated(uint16_t))
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    );

    /* Настройка параметров центрального виджета */

    QHBoxLayout* horizontal_lt = new QHBoxLayout(this);
    horizontal_lt->addWidget(_sender_wgt, false);
    horizontal_lt->addWidget(_receiver_wgt, true);

    this->setLayout(horizontal_lt);
}//------------------------------------------------------------------


TCentralWidget::~TCentralWidget() {
}//------------------------------------------------------------------
