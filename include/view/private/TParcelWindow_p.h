#ifndef TPARCELWINDOW_P_H
#define TPARCELWINDOW_P_H

#include "TParcelWindow.h"

class TParcelWindow::TParcelWindowPrivate
{
    Q_DECLARE_PUBLIC(TParcelWindow)

public:
    TParcelWindow * q_ptr;

    TParcelWindowPrivate();
    virtual ~TParcelWindowPrivate();

};//class TParcelWindow::TParcelWindowPrivate
//-------------------------------------------------------------------

#endif // TPARCELWINDOW_P_H
