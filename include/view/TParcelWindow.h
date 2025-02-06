#ifndef TPARCELWINDOW_H
#define TPARCELWINDOW_H

#include <QWidget>

class TParcelWindow : public QWidget
{
    Q_OBJECT

    class TParcelWindowPrivate;

public:
    explicit TParcelWindow(QWidget* parent = nullptr);
    virtual ~TParcelWindow();

protected:
    TParcelWindow(TParcelWindowPrivate &dd, QWidget *parent);
    TParcelWindowPrivate * const d_ptr;

private:
    Q_DECLARE_PRIVATE(TParcelWindow)

};//class TParcelWidget
//-------------------------------------------------------------------

#endif // TPARCELWINDOW_H
