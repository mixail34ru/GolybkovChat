#ifndef TPARCELWINDOW_P_H
#define TPARCELWINDOW_P_H

#include "TParcelWindow.h"
#include <QSortFilterProxyModel>

class TParcelWindowPrivate
{
    Q_DECLARE_PUBLIC(TParcelWindow)

public:
    explicit TParcelWindowPrivate(TModelStateInterface* model, TParcelWindow* qq);
    virtual ~TParcelWindowPrivate();

    QModelIndexList _list;

protected:
   TParcelWindow * const q_ptr;

};//class TParcelWindowPrivate
//-------------------------------------------------------------------

#endif // TPARCELWINDOW_P_H
