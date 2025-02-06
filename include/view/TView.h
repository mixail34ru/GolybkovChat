#ifndef TVIEW_H
#define TVIEW_H

#include "TPackageFormat.h"
#include <QObject>

class TModelStateInterface;

class TView : public QObject
{
    Q_OBJECT

    class TViewPrivate;

public:
    explicit TView(TModelStateInterface *model, QObject *parent = nullptr);
    virtual ~TView();

    void run();
    void show_parcel_edit();

signals:
    void sendActivated(ViewSendInfo info);
    void sendTimerActivated(uint timeout, ViewSendInfo info);
    void receiveActivated(uint16_t max_pack, uint16_t port);

protected:
    TView(TViewPrivate &dd, QObject *parent);
    TViewPrivate * const d_ptr;

private:
    Q_DECLARE_PRIVATE(TView)

}; //class TView
//-------------------------------------------------------------------

#endif // TVIEW_H
