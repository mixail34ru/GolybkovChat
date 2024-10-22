#include "TSenderWidget.h"

#include <QVBoxLayout>

TSenderWidget::TSenderWidget(TModelStateInterface* model, QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* vertical_lt = new QVBoxLayout(this);

    /* Информация в отправляемом пакете */

    _pack_data_grp_bx = new TSendDataGroupBox(this);
    vertical_lt->addWidget(_pack_data_grp_bx);

    /* Информация о получателе */

    _net_grp_bx = new TSendNetGroupBox(this);
    vertical_lt->addWidget(_net_grp_bx);

    /* Режим отправки */

    _mode_grp_bx = new TSendModeGroupBox(model, this);
    connect(_mode_grp_bx, &TSendModeGroupBox::send_activated,
        [this] () {
            try {
                SendInfo info {
                    _pack_data_grp_bx->get_package().value(),
                    _net_grp_bx->get_address().value()
                };

                emit send_activated(info);
            } catch(const std::bad_optional_access& e) { /**/ }
        }
    );

    connect(_mode_grp_bx, &TSendModeGroupBox::send_timer_activated,
        [this](uint timeout) {
            try {
                SendInfo info {
                    _pack_data_grp_bx->get_package().value(),
                    _net_grp_bx->get_address().value()
                };

                emit send_timer_activated(timeout, info);
            } catch(const std::bad_optional_access& e) { /**/ }
        }
    );

    vertical_lt->addWidget(_mode_grp_bx);
    vertical_lt->addStretch(1);

    /* Настройка параметров виджета */

    this->setLayout(vertical_lt);
}//------------------------------------------------------------------


TSenderWidget::~TSenderWidget() {
}//------------------------------------------------------------------
