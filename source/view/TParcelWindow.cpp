#include "TParcelWindow.h"
#include "TParcelWindow_p.h"

//#include "TSendDataGroupBox.h"

#include <QVBoxLayout>

/********************************************************************
 **********************  TParcelWindowPrivate  **********************
 *******************************************************************/

TParcelWindow::TParcelWindowPrivate::TParcelWindowPrivate() {
    // _send_data_gb = new TSendDataGroupBox(q_ptr);
    // QHBoxLayout* h_lt = new QHBoxLayout(q_ptr);

    // h_lt->addWidget(_send_data_gb);
    // q_ptr->setLayout(h_lt);
}//------------------------------------------------------------------


TParcelWindow::TParcelWindowPrivate::~TParcelWindowPrivate() {
}//------------------------------------------------------------------


/********************************************************************
 ************************   TParcelWindow   *************************
 *******************************************************************/


TParcelWindow::TParcelWindow(QWidget *parent)
    : QWidget(parent), d_ptr(new TParcelWindowPrivate())
{
    Q_D(TParcelWindow);
    d->q_ptr = this;
}//------------------------------------------------------------------


TParcelWindow::~TParcelWindow() {
}//------------------------------------------------------------------


TParcelWindow::TParcelWindow(TParcelWindowPrivate &dd, QWidget *parent)
    : QWidget(parent), d_ptr(&dd)
{
    Q_D(TParcelWindow);
    d->q_ptr = this;
}//------------------------------------------------------------------
