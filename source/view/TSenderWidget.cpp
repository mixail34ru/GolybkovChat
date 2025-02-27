#include "TSenderWidget.h"

#include "TModelStateInterface.h"
#include "TCorrectItemMap.h"

#include "TSendDataGroupBox.h"
#include "TSendNetGroupBox.h"
#include "TSendModeGroupBox.h"

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
    connect(
        _pack_data_grp_bx, &TSendDataGroupBox::addPackageActivated,
        this, &TSenderWidget::addSendPackageActivated
    );
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
    connect(
        _mode_grp_bx, &TSendModeGroupBox::EnteredUncorrectParams,
        this, &TSenderWidget::UpdateWidgetCorrectState
        );

    connect(_mode_grp_bx, &TSendModeGroupBox::sendActivated,
        [this] (uint num_pack) {
            try {
                NetAddress info = _net_grp_bx->get_address().value();

                emit sendActivated(info);
            } catch(const std::bad_optional_access& e) { /**/ }
        }
    );

    connect(_mode_grp_bx, &TSendModeGroupBox::sendTimerActivated,
        [this](uint timeout, uint num_pack) {
            try {
                NetAddress info = _net_grp_bx->get_address().value();

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
        _mode_grp_bx->SetEnableButtons(false);
    }
    else {
        _pack_data_grp_bx->SetEnableDataField(!flag);
        _net_grp_bx->SetEnableDataField(!flag);
        _mode_grp_bx->SetEnableButtons(!flag);
    }
}//------------------------------------------------------------------


void TSenderWidget::UpdateWidgetCorrectState(QObject* obj, bool flag) {
    _correct_map->SetItemStatus(obj, flag);
}//------------------------------------------------------------------


void TSenderWidget::SetEnableSending(bool flag) {
    _mode_grp_bx->SetEnableButtons(flag);
}//------------------------------------------------------------------
