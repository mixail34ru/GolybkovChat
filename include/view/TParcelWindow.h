#ifndef TPARCELWINDOW_H
#define TPARCELWINDOW_H

#include "TPackageFormat.h"

#include <QWidget>
#include <QScopedPointer>


class TModelStateInterface;
class TParcelWindowPrivate;

class TParcelWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TParcelWindow(
        TModelStateInterface* model, QWidget* parent = nullptr);
    virtual ~TParcelWindow();

signals:
    void addSendPackageActivated(ViewSendPackage pack);
    void delSendPackageActivated(int index);
    void clearSendStorageActivated();

protected:
    TParcelWindow(TParcelWindowPrivate &dd);
    QScopedPointer<TParcelWindowPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(TParcelWindow)

};//class TParcelWidget
//-------------------------------------------------------------------

#endif // TPARCELWINDOW_H
