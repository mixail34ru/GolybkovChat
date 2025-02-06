#ifndef TVIEW_P_H
#define TVIEW_P_H

#include "TView.h"
#include <QPointer>

class TModelStateInterface;

class TMainWindow;
class TParcelWindow;

class TView::TViewPrivate {
    Q_DECLARE_PUBLIC(TView)

public:
    TView * q_ptr;

    TViewPrivate(TModelStateInterface *model);
    virtual ~TViewPrivate();

    QPointer<TMainWindow> _main_wnd;
    void run();

    QPointer<TParcelWindow> _parcel_wnd;
    void show_parcel_edit();

}; //class TView::TViewPrivate
//-------------------------------------------------------------------

#endif // TVIEW_P_H
