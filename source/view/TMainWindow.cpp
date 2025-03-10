#include "TMainWindow.h"
#include "TCentralWidget.h"

TMainWindow::TMainWindow(TModelStateInterface* model, QWidget *parent)
    : QMainWindow(parent)
{
    /* Настройка центрального виджета */

    _central_wgt = new TCentralWidget(model, this);

    connect(
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
    );

    /* Настройка параметров главного окна */

    this->setMinimumSize(640, 510);
    this->setCentralWidget(_central_wgt);
    this->show();
}//------------------------------------------------------------------


TMainWindow::~TMainWindow() {
}//------------------------------------------------------------------

void TMainWindow::closeEvent(QCloseEvent *event)
{
    emit closed();
}
