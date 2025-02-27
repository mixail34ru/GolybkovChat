#ifndef TSENDERWIDGET_H
#define TSENDERWIDGET_H

#include "TPackageFormat.h"

#include <QWidget>
#include <QPushButton>
#include <functional>

class TModelStateInterface;
class TCorrectItemMap;
class TSendDataGroupBox;
class TSendNetGroupBox;
class TSendModeGroupBox;


class TSenderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TSenderWidget(
        TModelStateInterface* model, QWidget* parent = nullptr);
    ~TSenderWidget();

signals:
    void showParcelEditActivated();
    void addSendPackageActivated(ViewSendPackage pack);

    void sendActivated(NetAddress info);
    void sendTimerActivated(uint timeout, NetAddress info);

private:
    std::function<bool(void)> CheckTimerSendingStatus;

    TCorrectItemMap* _correct_map;

    TSendDataGroupBox* _pack_data_grp_bx;
    QPushButton* _parcel_edit_btn;
    TSendNetGroupBox* _net_grp_bx;
    TSendModeGroupBox* _mode_grp_bx;

private slots:
    void SwitchFieldEdit(bool flag);
    void UpdateWidgetCorrectState(QObject* obj, bool flag);
    void SetEnableSending(bool flag);

}; //class TSenderWidget
//-------------------------------------------------------------------

#endif // TSENDERWIDGET_H
