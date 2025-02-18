#ifndef TSENDERWIDGET_H
#define TSENDERWIDGET_H

#include "TPackageFormat.h"

#include <QWidget>
#include <QPushButton>
#include <functional>

#include <functional>

class TModelStateInterface;
class TCorrectItemMap;
<<<<<<< HEAD
class TSendDataGroupBox;
class TSendNetGroupBox;
class TSendModeGroupBox;

=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

class TSenderWidget : public QWidget
{
    Q_OBJECT

<<<<<<< HEAD
=======
    std::function<bool(void)> CheckTimerSendingStatus;

    TCorrectItemMap* _correct_map;

    TSendDataGroupBox* _pack_data_grp_bx;
    TSendNetGroupBox* _net_grp_bx;
    TSendModeGroupBox* _mode_grp_bx;

>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
public:
    explicit TSenderWidget(
        TModelStateInterface* model, QWidget* parent = nullptr);
    ~TSenderWidget();

private slots:
    void SwitchFieldEdit(bool flag);
    void UpdateWidgetCorrectState(QObject* obj, bool flag);
    void SetEnableSending(bool flag);

signals:
<<<<<<< HEAD
    void showParcelEditActivated();
    void addSendPackageActivated(ViewSendPackage pack);

    void sendActivated(ViewSendInfo info);
    void sendTimerActivated(uint timeout, ViewSendInfo info);

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
=======
    void sendActivated(ViewSendInfo info);
    void sendTimerActivated(uint timeout, ViewSendInfo info);
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

}; //class TSenderWidget
//-------------------------------------------------------------------

#endif // TSENDERWIDGET_H
