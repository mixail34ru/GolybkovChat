#include "TView.h"
#include "TView_p.h"

#include "TModelStateInterface.h"
#include "TMainWindow.h"
#include "TParcelWindow.h"

/********************************************************************
 ***********************   TViewPrivate  ****************************
 *******************************************************************/

TView::TViewPrivate::TViewPrivate(TModelStateInterface *model)
    : _model(model)
{
    _main_wnd = new TMainWindow(model);


    connect(
        _main_wnd, &TMainWindow::showParcelEditActivated,
        [this](auto... arg){
            show_parcel_edit();
        });
    connect(
        _main_wnd, &TMainWindow::addSendPackageActivated,
        [this](auto... arg){
            Q_Q(TView);
            emit(q->addSendPackageActivated(arg...));
        });

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
        _main_wnd, &TMainWindow::clearReceiveStorageActivated,
        [this](auto... arg) {
            Q_Q(TView);
            emit(q->clearReceiveStorageActivated(arg...));
        });
    connect(
        _main_wnd, &TMainWindow::closed,
        [this](){
            if (!_parcel_wnd.isNull())
                _parcel_wnd->close();
        });

}//------------------------------------------------------------------


TView::TViewPrivate::~TViewPrivate() {
}//------------------------------------------------------------------


void TView::TViewPrivate::run() {
    _main_wnd->show();
}//------------------------------------------------------------------


void TView::TViewPrivate::show_parcel_edit() {
    if (!_parcel_wnd) {
        Q_Q(TView);

        _parcel_wnd = new TParcelWindow(_model);
        connect(
            _parcel_wnd, &TParcelWindow::addSendPackageActivated,
            q, &TView::addSendPackageActivated
        );
        connect(
            _parcel_wnd, &TParcelWindow::delSendPackageActivated,
            q, &TView::delSendPackageActivated
        );
        connect(
            _parcel_wnd, &TParcelWindow::clearSendStorageActivated,
            q, &TView::clearSendStorageActivated
        );
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

