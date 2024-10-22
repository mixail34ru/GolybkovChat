#include "TMainWindow.h"

TMainWindow::TMainWindow(TModelStateInterface* model, QWidget *parent)
    : QMainWindow(parent)
{
    /* Настройка центрального виджета */

    _central_wgt = new TCentralWidget(model, this);
    connect(
        _central_wgt, &TCentralWidget::send_activated,
        this, &TMainWindow::send_package_activated
    );
    connect(
        _central_wgt, &TCentralWidget::send_timer_activated,
        this, &TMainWindow::send_timer_package_activated
    );

    /* Настройка параметров главного окна */

    this->setMinimumSize(640, 480);
    this->setCentralWidget(_central_wgt);
    this->show();
}//------------------------------------------------------------------


TMainWindow::~TMainWindow() {
}//------------------------------------------------------------------
