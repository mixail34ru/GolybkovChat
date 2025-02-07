#include "TView.h"
#include "TView_p.h"

#include "TMainWindow.h"
#include "TParcelWindow.h"

/********************************************************************
 ***********************   TViewPrivate  ****************************
 *******************************************************************/

TView::TViewPrivate::TViewPrivate(TModelStateInterface *model) {
    _main_wnd = new TMainWindow(model);

    connect(
        _main_wnd, &TMainWindow::sendActivated,
        [this](auto... arg) {
            Q_Q(TView);
            emit(q->sendActivated(arg...));
        });
    connect(
        _main_wnd, &TMainWindow::sendTimerActivated,
        [this](auto... arg) {
            Q_Q(TView);
            emit(q->sendTimerActivated(arg...));
        });
    connect(
        _main_wnd, &TMainWindow::receiveActivated,
        [this](auto... arg) {
            Q_Q(TView);
            emit(q->receiveActivated(arg...));
        });
    connect(
        _main_wnd,  &TMainWindow::addPackageActivated,
        [this](auto... arg){
            Q_Q(TView);
            emit(q->addPackageActivated(arg...));
        });
    connect(
        _main_wnd,  &TMainWindow::showParcelEditActivated,
        [this](){
            show_parcel_edit();
        });
}//------------------------------------------------------------------


TView::TViewPrivate::~TViewPrivate() {
}//------------------------------------------------------------------


void TView::TViewPrivate::run() {
    _main_wnd->show();
}//------------------------------------------------------------------


void TView::TViewPrivate::show_parcel_edit() {
    if (!_parcel_wnd) {
        _parcel_wnd = new TParcelWindow();
    }

    _parcel_wnd->show();
}//------------------------------------------------------------------


/********************************************************************
 ***************************   TView   ******************************
 *******************************************************************/

TView::TView(TModelStateInterface *model, QObject *parent)
    : QObject(parent), d_ptr(new TViewPrivate(model))
{
    Q_D(TView);
    d->q_ptr = this;
}//------------------------------------------------------------------


TView::~TView() {
}//------------------------------------------------------------------


TView::TView(TViewPrivate &dd, QObject *parent)
    : QObject(parent), d_ptr(&dd)
{
    Q_D(TView);
    d->q_ptr = this;
}//------------------------------------------------------------------


void TView::run() {
    Q_D(TView);
    d->run();
}//------------------------------------------------------------------


void TView::show_parcel_edit() {
    Q_D(TView);
    d->show_parcel_edit();
}//------------------------------------------------------------------
