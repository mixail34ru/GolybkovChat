#include "TSendModeGroupBox.h"

#include "TModelStateInterface.h"

TSendModeGroupBox::TSendModeGroupBox(TModelStateInterface* model, QWidget* parent)
    : QGroupBox(parent)
{
    CheckSendingStatus
        = [model]()->bool const { return model->IsSending(); };

    /* Варианты режимов */

    _mode_cmb_bx = new QComboBox(this);
    _mode_cmb_bx->addItem("Одиночное сообщение");
    _mode_cmb_bx->addItem("Периодическая отправка");
    _mode_cmb_bx->addItem("Совмещенный режим");
    connect(
        _mode_cmb_bx, SIGNAL(currentIndexChanged(int)),
        this, SLOT(SetCurrentMode(int))
    );

    /* Одиночное сообщение */

    _send_btn = new QPushButton("Отправка", this);
    connect(_send_btn, &QPushButton::clicked,
        [this] () {
            _send_btn->setEnabled(false);
            emit send_activated();
        }
    );
    connect(
        model, SIGNAL(StatusSendingChanged(bool)),
        this, SLOT(SetStatus_send_btn(bool))
    );

    /* Периодическая отправка */

    _timeout_ln_edit = new QLineEdit("1000", this);

    _send_timer_btn = new QPushButton("Начать отправку", this);
    connect(_send_timer_btn, &QPushButton::clicked,
        [this] () {
            try {
                _send_timer_btn->setEnabled(false);
                emit send_timer_activated(_timeout_ln_edit->text().toUInt());
            } catch (...) {}
        }
    );
    connect(
        model, SIGNAL(StatusSendingTimerChanged(bool)),
        this, SLOT(SetStatus_send_timer_btn(bool))
    );

    /* Настройка параметров виджета */

    _send_frm_lt = new QFormLayout(this);
    _send_frm_lt->addRow("Режим:", _mode_cmb_bx);
    _send_frm_lt->addRow("Интервал, мс:", _timeout_ln_edit);
    _send_frm_lt->addRow(_send_timer_btn);
    _send_frm_lt->addRow(_send_btn);

    SetCurrentMode(_mode_cmb_bx->currentIndex());

    this->setTitle("Режим отправки");
    this->setLayout(_send_frm_lt);
}//------------------------------------------------------------------


TSendModeGroupBox::~TSendModeGroupBox() {
}//------------------------------------------------------------------


void TSendModeGroupBox::SetCurrentMode(int index) {
    if (index >= 0 && index < _mode_cmb_bx->count()) {
        if (CheckSendingStatus()) {
            try {
                _send_timer_btn->setEnabled(false);
                emit send_timer_activated(_timeout_ln_edit->text().toUInt());
            } catch (...) {}
        }

        switch(index) {
        case 0: /* Одиночное сообщение */
            _send_frm_lt->setRowVisible(_timeout_ln_edit, false);
            _send_frm_lt->setRowVisible(_send_timer_btn, false);
            _send_btn->setText("Отправка");
            _send_frm_lt->setRowVisible(_send_btn, true);
            break;
        case 1: /* Периодическая отправка */
            _send_frm_lt->setRowVisible(_timeout_ln_edit, true);
            _send_frm_lt->setRowVisible(_send_timer_btn, true);
            _send_frm_lt->setRowVisible(_send_btn, false);
            break;
        default:
            _send_frm_lt->setRowVisible(_timeout_ln_edit, true);
            _send_frm_lt->setRowVisible(_send_timer_btn, true);
            _send_btn->setText("Одиночное сообщение");
            _send_frm_lt->setRowVisible(_send_btn, true);
            break;
        }
    }
}//------------------------------------------------------------------


void TSendModeGroupBox::SetStatus_send_timer_btn(bool flag) {
    if (flag) _send_timer_btn->setText("Остановить отправку");
    else _send_timer_btn->setText("Начать отправку");

    _send_timer_btn->setEnabled(true);
}//------------------------------------------------------------------


void TSendModeGroupBox::SetStatus_send_btn(bool flag) {
    _send_btn->setEnabled(true);
}//------------------------------------------------------------------
