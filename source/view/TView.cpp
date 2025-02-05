#include "TView.h"
#include "TMainWindow.h"

struct TView::Impl {
    std::unique_ptr<TMainWindow> _main_wnd;
};//struct TView::Impl
//-------------------------------------------------------------------


TView::TView(TModelStateInterface *model, QObject *parent)
    : QObject(parent), pImpl(std::make_unique<Impl>())
{
    pImpl->_main_wnd = std::make_unique<TMainWindow>(model);

    connect(
        pImpl->_main_wnd.get(), &TMainWindow::sendActivated,
        this, &TView::sendActivated);
    connect(
        pImpl->_main_wnd.get(), &TMainWindow::sendTimerActivated,
        this, &TView::sendTimerActivated);
    connect(
        pImpl->_main_wnd.get(), &TMainWindow::receiveActivated,
        this, &TView::receiveActivated);
}//------------------------------------------------------------------


TView::~TView() {
}//------------------------------------------------------------------


void TView::run() {
    pImpl->_main_wnd->show();
}//------------------------------------------------------------------
