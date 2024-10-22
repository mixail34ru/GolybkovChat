#ifndef TSENDERWIDGET_H
#define TSENDERWIDGET_H

#include "TPackageFormat.h"

#include "TSendDataGroupBox.h"
#include "TSendNetGroupBox.h"
#include "TSendModeGroupBox.h"

#include <QWidget>

class TModelStateInterface;

class TSenderWidget : public QWidget
{
    Q_OBJECT

    TSendDataGroupBox* _pack_data_grp_bx;
    TSendNetGroupBox* _net_grp_bx;
    TSendModeGroupBox* _mode_grp_bx;

public:
    TSenderWidget(TModelStateInterface* model, QWidget* parent = nullptr);
    ~TSenderWidget();

signals:
    void send_activated(SendInfo info);
    void send_timer_activated(uint timeout, SendInfo info);

}; //class TSenderWidget
//-------------------------------------------------------------------

#endif // TSENDERWIDGET_H
