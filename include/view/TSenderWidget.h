#ifndef TSENDERWIDGET_H
#define TSENDERWIDGET_H

#include "TPackageFormat.h"

#include "TSendDataGroupBox.h"
#include "TSendNetGroupBox.h"
#include "TSendModeGroupBox.h"

#include <QWidget>

#include <functional>

class TModelStateInterface;
class TCorrectItemMap;

class TSenderWidget : public QWidget
{
    Q_OBJECT

    std::function<bool(void)> CheckTimerSendingStatus;

    TCorrectItemMap* _correct_map;

    TSendDataGroupBox* _pack_data_grp_bx;
    QPushButton* _parcel_edit_btn;
    TSendNetGroupBox* _net_grp_bx;
    TSendModeGroupBox* _mode_grp_bx;

public:
    TSenderWidget(TModelStateInterface* model, QWidget* parent = nullptr);
    ~TSenderWidget();

private slots:
    void SwitchFieldEdit(bool flag);
    void UpdateWidgetCorrectState(QObject* obj, bool flag);
    void SetEnableSending(bool flag);

signals:
    void sendActivated(ViewSendInfo info);
    void sendTimerActivated(uint timeout, ViewSendInfo info);
    void addPackageActivated(ViewSendPackage pack);
    void showParcelEditActivated();

}; //class TSenderWidget
//-------------------------------------------------------------------

#endif // TSENDERWIDGET_H
