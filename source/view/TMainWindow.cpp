#include "TMainWindow.h"
#include "TCentralWidget.h"

TMainWindow::TMainWindow(TModelStateInterface* model, QWidget *parent)
    : QMainWindow(parent)
{
    /* Настройка центрального виджета */

    _central_wgt = new TCentralWidget(model, this);

    connect(
<<<<<<< HEAD
        _central_wgt, &TCentralWidget::showParcelEditActivated,
        this, &TMainWindow::showParcelEditActivated
    );
    connect(
        _central_wgt, &TCentralWidget::addSendPackageActivated,
        this, &TMainWindow::addSendPackageActivated
        );

    connect(
        _central_wgt, &TCentralWidget::sendActivated,
        this, &TMainWindow::sendActivated
    );
    connect(
        _central_wgt, &TCentralWidget::sendTimerActivated,
        this, &TMainWindow::sendTimerActivated
    );

    connect(
        _central_wgt, &TCentralWidget::receivePackageActivated,
        this, &TMainWindow::receiveActivated
    );
    connect(
        _central_wgt, &TCentralWidget::clearReceiveStorageActivated,
        this, &TMainWindow::clearReceiveStorageActivated
=======
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
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    );

    /* Настройка параметров главного окна */

    this->setMinimumSize(640, 510);
    this->setCentralWidget(_central_wgt);
    this->show();
}//------------------------------------------------------------------


TMainWindow::~TMainWindow() {
}//------------------------------------------------------------------
