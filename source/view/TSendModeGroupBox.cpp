#include "TSendModeGroupBox.h"

#include "TModelStateInterface.h"
#include "TCorrectItemMap.h"

#include <climits>

TSendModeGroupBox::TSendModeGroupBox(TModelStateInterface* model, QWidget* parent)
    : QGroupBox(parent)
{
    _correct_map = new TCorrectItemMap(this);

    CheckTimerSendingStatus
        = [model]()->bool const { return model->IsTimerSending(); };

    _pack_ln_edit = new QLineEdit("1", this);
    _pack_ln_edit->setValidator(new QIntValidator(1, USHRT_MAX, _pack_ln_edit));
    connect(
        _pack_ln_edit, SIGNAL(textChanged(QString)),
        this, SLOT(check_pack_ln_edit(QString))
        );

    /* Варианты режимов */

    _mode_cmb_bx = new QComboBox(this);
    _mode_cmb_bx->addItem("Одиночное сообщение");
    _mode_cmb_bx->addItem("Периодическая отправка");
    _mode_cmb_bx->addItem("Совмещенный режим");
    connect(
        _mode_cmb_bx, SIGNAL(currentIndexChanged(int)),
        this, SLOT(setCurrentMode(int))
    );
    _correct_map->EmplaceItem(_pack_ln_edit, true);

    /* Одиночное сообщение */

    _send_btn = new QPushButton("Отправка", this);
    connect(_send_btn, &QPushButton::clicked,
        [this] () {
            _send_btn->setEnabled(false);
            _pack_ln_edit->setEnabled(false);
            emit sendActivated(_pack_ln_edit->text().toUInt());
        }
    );
    connect(
        model, SIGNAL(statusSendingChanged(bool)),
        this, SLOT(setStatus_send_btn(bool))
    );

    /* Периодическая отправка */

    _timeout_ln_edit = new QLineEdit("1000", this);
    _timeout_ln_edit->setValidator(new QIntValidator(1, INT_MAX, _timeout_ln_edit));
    connect(
        _timeout_ln_edit, SIGNAL(textChanged(QString)),
        this, SLOT(check_timeout_ln_edit(QString))
    );

    _correct_map->EmplaceItem(_timeout_ln_edit, true);

    _send_timer_btn = new QPushButton("Начать отправку", this);
    connect(_send_timer_btn, &QPushButton::clicked,
        [this] () {
            try {
                _send_timer_btn->setEnabled(false);
                _pack_ln_edit->setEnabled(false);
                _timeout_ln_edit->setEnabled(false);
                emit sendTimerActivated(_timeout_ln_edit->text().toUInt(), _pack_ln_edit->text().toUInt());
            } catch (...) {}
        }
    );
    connect(
        model, SIGNAL(statusSendingTimerChanged(bool)),
        this, SLOT(setStatus_send_timer_btn(bool))
    );


    /* Настройка параметров виджета */

    _send_frm_lt = new QFormLayout(this);
    _send_frm_lt->addRow("Режим:", _mode_cmb_bx);
    _send_frm_lt->addRow("Интервал, мс:", _timeout_ln_edit);
    _send_frm_lt->addRow("Кол-во пакетов:", _pack_ln_edit);
    _send_frm_lt->addRow(_send_timer_btn);
    _send_frm_lt->addRow(_send_btn);

    setCurrentMode(_mode_cmb_bx->currentIndex());

    this->setTitle("Режим отправки");
    this->setLayout(_send_frm_lt);
}//------------------------------------------------------------------


TSendModeGroupBox::~TSendModeGroupBox() {
}//------------------------------------------------------------------


void TSendModeGroupBox::setCurrentMode(int index) {
    if (index >= 0 && index < _mode_cmb_bx->count()) {
        if (CheckTimerSendingStatus()) {
            try {
                _send_timer_btn->setEnabled(false);
                emit sendTimerActivated(_timeout_ln_edit->text().toUInt(), _pack_ln_edit->text().toUInt());
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


void TSendModeGroupBox::setStatus_send_timer_btn(bool flag) {
    if (flag) {
        _send_timer_btn->setText("Остановить отправку");
    }
    else {
       _send_timer_btn->setText("Начать отправку");
       _timeout_ln_edit->setEnabled(true);
       _pack_ln_edit->setEnabled(true);
    }

    _send_timer_btn->setEnabled(true); 
}//------------------------------------------------------------------


void TSendModeGroupBox::setStatus_send_btn(bool flag) {
    _pack_ln_edit->setEnabled(true);
    _send_btn->setEnabled(true);
}//------------------------------------------------------------------


void TSendModeGroupBox::SetEnableButtons(bool flag) {
    _send_btn->setEnabled(flag);
    if (!CheckTimerSendingStatus())
        _send_timer_btn->setEnabled(flag && _correct_map->GetItemStatus(_timeout_ln_edit)&&_correct_map->GetItemStatus(_pack_ln_edit));
}//------------------------------------------------------------------


void TSendModeGroupBox::check_pack_ln_edit(const QString& text){
    unsigned int num = text.toUInt();
    if(num > 0 && num <= 300)
    {
        _pack_ln_edit->setStyleSheet("QLineEdit { color: black }");
        _correct_map->SetItemStatus(_pack_ln_edit, true);

        _send_btn->setEnabled(true);
    }
    else
    {
        _pack_ln_edit->setStyleSheet("QLineEdit { color: red }");
        _correct_map->SetItemStatus(_pack_ln_edit, false);

        _send_btn->setEnabled(false);
    }
}


void TSendModeGroupBox::check_timeout_ln_edit(const QString& text) {
    unsigned long num = text.toULong();
    if (num > 0 && num <= INT_MAX) {
        _timeout_ln_edit->setStyleSheet("QLineEdit { color: black }");
        _correct_map->SetItemStatus(_timeout_ln_edit, true);

        _send_timer_btn->setEnabled(true);
    }
    else {
        _timeout_ln_edit->setStyleSheet("QLineEdit { color: red }");
        _correct_map->SetItemStatus(_timeout_ln_edit, false);

        _send_timer_btn->setEnabled(false);
    }
}//------------------------------------------------------------------
