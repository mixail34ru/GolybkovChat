#include "TMainWindow.h"

TMainWindow::TMainWindow(TModelStateInterface* model, QWidget *parent)
    : QMainWindow(parent)
{
    /* Настройка центрального виджета */

    _central_wgt = new TCentralWidget(model, this);
    connect(
        _central_wgt, &TCentralWidget::sendActivated,
        this, &TMainWindow::sendActivated
    );
    connect(
        _central_wgt, &TCentralWidget::sendTimerActivated,
        this, &TMainWindow::sendTimerActivated
    );
    connect(
        _central_wgt, SIGNAL(receivePackageActivated(uint16_t)),
        this, SIGNAL(receiveActivated(uint16_t))
    );

    /* Настройка параметров главного окна */

    this->setMinimumSize(640, 480);
    this->setCentralWidget(_central_wgt);
    this->show();
}//------------------------------------------------------------------


TMainWindow::~TMainWindow() {
}//------------------------------------------------------------------
