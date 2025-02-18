#include "TSenderWidget.h"

#include "TModelStateInterface.h"
#include "TCorrectItemMap.h"

<<<<<<< HEAD
#include "TSendDataGroupBox.h"
#include "TSendNetGroupBox.h"
#include "TSendModeGroupBox.h"

=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
#include <QVBoxLayout>

TSenderWidget::TSenderWidget(TModelStateInterface* model, QWidget* parent)
    : QWidget(parent)
{
    CheckTimerSendingStatus
        = [model]()->bool const { return model->IsTimerSending(); };

    connect(
        model, SIGNAL(statusSendingTimerChanged(bool)),
        this, SLOT(SwitchFieldEdit(bool))
    );

    connect(
        model, SIGNAL(statusSendingChanged(bool)),
        this, SLOT(SwitchFieldEdit(bool))
    );

    _correct_map = new TCorrectItemMap(this);

    QVBoxLayout* vertical_lt = new QVBoxLayout(this);

    /* Содержимое добавляемого в посылку пакета */

    _pack_data_grp_bx = new TSendDataGroupBox(this);
    connect(
        _pack_data_grp_bx, &TSendDataGroupBox::EnteredUncorrectParams,
        this, &TSenderWidget::UpdateWidgetCorrectState
    );
<<<<<<< HEAD
    connect(
        _pack_data_grp_bx, &TSendDataGroupBox::addPackageActivated,
        this, &TSenderWidget::addSendPackageActivated
    );
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    _correct_map->EmplaceItem(_pack_data_grp_bx, true);
    vertical_lt->addWidget(_pack_data_grp_bx);

    /* Кнопка отображения содержимого посылки */

    _parcel_edit_btn = new QPushButton("Редактировать посылку", this);
    connect(
        _parcel_edit_btn, &QPushButton::clicked,
        this, &TSenderWidget::showParcelEditActivated
    );
    vertical_lt->addWidget(_parcel_edit_btn);

    /* Информация о получателе */

    _net_grp_bx = new TSendNetGroupBox(this);
    connect(
        _net_grp_bx, &TSendNetGroupBox::EnteredUncorrectParams,
        this, &TSenderWidget::UpdateWidgetCorrectState
    );
    _correct_map->EmplaceItem(_net_grp_bx, true);
    vertical_lt->addWidget(_net_grp_bx);

    /* Режим отправки */

    _mode_grp_bx = new TSendModeGroupBox(model, this);
    _correct_map->EmplaceItem(_mode_grp_bx, true);
<<<<<<< HEAD
    connect(
        _mode_grp_bx, &TSendModeGroupBox::EnteredUncorrectParams,
        this, &TSenderWidget::UpdateWidgetCorrectState
        );

    connect(_mode_grp_bx, &TSendModeGroupBox::sendActivated,
        [this] (uint num_pack) {
            try {
                ViewSendInfo info {
                    num_pack,
=======
    connect(_mode_grp_bx, &TSendModeGroupBox::sendActivated,
        [this] () {
            try {
                ViewSendInfo info {
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
                    _pack_data_grp_bx->get_package().value(),
                    _net_grp_bx->get_address().value()
                };

                emit sendActivated(info);
            } catch(const std::bad_optional_access& e) { /**/ }
        }
    );

    connect(_mode_grp_bx, &TSendModeGroupBox::sendTimerActivated,
<<<<<<< HEAD
        [this](uint timeout, uint num_pack) {
            try {
                ViewSendInfo info {
                    num_pack,
=======
        [this](uint timeout) {
            try {
                ViewSendInfo info {
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
                    _pack_data_grp_bx->get_package().value(),
                    _net_grp_bx->get_address().value()
                };

                emit sendTimerActivated(timeout, info);
            } catch(const std::bad_optional_access& e) { /**/ }
        }
    );

    connect(
        _correct_map, SIGNAL(CorrectStatusChanged(bool)),
        this, SLOT(SetEnableSending(bool))
    );

    vertical_lt->addWidget(_mode_grp_bx);
    vertical_lt->addStretch(1);

    /* Настройка параметров виджета */

    this->setLayout(vertical_lt);
}//------------------------------------------------------------------


TSenderWidget::~TSenderWidget() {
}//------------------------------------------------------------------


void TSenderWidget::SwitchFieldEdit(bool flag) {
    if (CheckTimerSendingStatus()) {
        _pack_data_grp_bx->SetEnableDataField(false);
        _net_grp_bx->SetEnableDataField(false);
<<<<<<< HEAD
        _mode_grp_bx->SetEnableButtons(false);
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    }
    else {
        _pack_data_grp_bx->SetEnableDataField(!flag);
        _net_grp_bx->SetEnableDataField(!flag);
<<<<<<< HEAD
        _mode_grp_bx->SetEnableButtons(!flag);
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    }
}//------------------------------------------------------------------


void TSenderWidget::UpdateWidgetCorrectState(QObject* obj, bool flag) {
    _correct_map->SetItemStatus(obj, flag);
}//------------------------------------------------------------------


void TSenderWidget::SetEnableSending(bool flag) {
    _mode_grp_bx->SetEnableButtons(flag);
}//------------------------------------------------------------------
