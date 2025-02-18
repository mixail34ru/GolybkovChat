#include "TSendModeGroupBox.h"
#include "TUShortValidator.h"
#include "TIntValidator.h"

#include "TModelStateInterface.h"
#include "TCorrectItemMap.h"

#include <climits>

TSendModeGroupBox::TSendModeGroupBox(TModelStateInterface* model, QWidget* parent)
    : QGroupBox(parent)
{
    _correct_map = new TCorrectItemMap(this);
<<<<<<< HEAD
    connect(
        _correct_map, &TCorrectItemMap::CorrectStatusChanged,
        [this] (auto arg) { emit EnteredUncorrectParams(this, arg); }
        );

    CheckTimerSendingStatus
        = [model]()->bool const { return model->IsTimerSending(); };

    /* Количество пакетов */

    _pack_ln_edit = new TCustomLineEdit(new TUShortValidator(1,  300, this), "1", this);
    _pack_ln_edit->setFocusPolicy(Qt::ClickFocus);
    connect(
        _pack_ln_edit, &TCustomLineEdit::EnteredCorrectParams,
        [this](auto arg) { _correct_map->SetItemStatus(_pack_ln_edit, arg);}
    );
    connect(
        _pack_ln_edit, &QLineEdit::editingFinished,
        [this]() { _pack_ln_edit->delete_Null();}
    );
=======

    CheckTimerSendingStatus
        = [model]()->bool const { return model->IsTimerSending(); };
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

    /* Варианты режимов */

    _mode_cmb_bx = new QComboBox(this);
    _mode_cmb_bx->addItem("Совмещенный режим");
    _mode_cmb_bx->addItem("Периодическая отправка");
    _mode_cmb_bx->addItem("Одиночное сообщение");
    connect(
        _mode_cmb_bx, SIGNAL(currentIndexChanged(int)),
        this, SLOT(setCurrentMode(int))
    );

    /* Одиночное сообщение */

    _send_btn = new QPushButton("Отправка", this);
    connect(_send_btn, &QPushButton::clicked,
        [this] () {
            _send_btn->setEnabled(false);
<<<<<<< HEAD
            _pack_ln_edit->setEnabled(false);
            emit sendActivated(_pack_ln_edit->text().toUInt());
=======
            emit sendActivated();
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
        }
    );
    connect(
        model, SIGNAL(statusSendingChanged(bool)),
        this, SLOT(setStatus_send_btn(bool))
    );

    /* Периодическая отправка */

<<<<<<< HEAD
    _timeout_ln_edit = new TCustomLineEdit(new TIntValidator(0, this), "1000", this);
    _timeout_ln_edit->setFocusPolicy(Qt::ClickFocus);
    connect(
        _timeout_ln_edit, &TCustomLineEdit::EnteredCorrectParams,
        [this](auto arg) { _correct_map->SetItemStatus(_timeout_ln_edit, arg); }
    );
    connect(
        _timeout_ln_edit, &QLineEdit::editingFinished,
        [this]() { _timeout_ln_edit->delete_Null();}
    );
=======
    _timeout_ln_edit = new QLineEdit("1000", this);
    _timeout_ln_edit->setValidator(new QIntValidator(1, INT_MAX, _timeout_ln_edit));
    connect(
        _timeout_ln_edit, SIGNAL(textChanged(QString)),
        this, SLOT(check_timeout_ln_edit(QString))
    );

    _correct_map->EmplaceItem(_timeout_ln_edit, true);
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

    _send_timer_btn = new QPushButton("Начать отправку", this);
    connect(_send_timer_btn, &QPushButton::clicked,
        [this] () {
            try {
                _send_timer_btn->setEnabled(false);
<<<<<<< HEAD
                _pack_ln_edit->setEnabled(false);
                _timeout_ln_edit->setEnabled(false);
                emit sendTimerActivated(_timeout_ln_edit->text().toUInt(), _pack_ln_edit->text().toUInt());
=======
                _timeout_ln_edit->setEnabled(false);
                emit sendTimerActivated(_timeout_ln_edit->text().toUInt());
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
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
<<<<<<< HEAD
                emit sendTimerActivated(_timeout_ln_edit->text().toUInt(), _pack_ln_edit->text().toUInt());
=======
                emit sendTimerActivated(_timeout_ln_edit->text().toUInt());
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
            } catch (...) {}
        }

        _correct_map->Clear();
        _correct_map->EmplaceItem(_pack_ln_edit, _pack_ln_edit->getCorrect());

        switch(index) {
        case 0: /* Совмещенный режим */
            // Реинициализирую карту
            _correct_map->EmplaceItem(_timeout_ln_edit, _timeout_ln_edit->getCorrect());

            _send_frm_lt->setRowVisible(_timeout_ln_edit, true);
            _send_frm_lt->setRowVisible(_send_timer_btn, true);
            _send_btn->setText("Одиночное сообщение");
            _send_frm_lt->setRowVisible(_send_btn, true);
            break;
        case 1: /* Периодическая отправка */
            // Реинициализирую карту
            _correct_map->EmplaceItem(_timeout_ln_edit, _timeout_ln_edit->getCorrect());

            _send_frm_lt->setRowVisible(_timeout_ln_edit, true);
            _send_frm_lt->setRowVisible(_send_timer_btn, true);
            _send_frm_lt->setRowVisible(_send_btn, false);
            break;
        default: /* Одиночное сообщение */
            _send_frm_lt->setRowVisible(_timeout_ln_edit, false);
            _send_frm_lt->setRowVisible(_send_timer_btn, false);
            _send_btn->setText("Отправка");
            _send_frm_lt->setRowVisible(_send_btn, true);
            break;
        }
    }
    emit EnteredUncorrectParams(this, _correct_map->Status());
}//------------------------------------------------------------------


void TSendModeGroupBox::setStatus_send_timer_btn(bool flag) {
    if (flag) {
        _send_timer_btn->setText("Остановить отправку");
    }
    else {
       _send_timer_btn->setText("Начать отправку");
<<<<<<< HEAD
       _timeout_ln_edit->setEnabled(true);
       _pack_ln_edit->setEnabled(true);
    }
    _send_btn->setEnabled(true);
    _send_timer_btn->setEnabled(true);
=======
        _timeout_ln_edit->setEnabled(true);
    }

    _send_timer_btn->setEnabled(true); 
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
}//------------------------------------------------------------------


void TSendModeGroupBox::setStatus_send_btn(bool flag) {
<<<<<<< HEAD
    _pack_ln_edit->setEnabled(_timeout_ln_edit->isEnabled());
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    _send_btn->setEnabled(true);
    _send_timer_btn->setEnabled(true);
}//------------------------------------------------------------------


void TSendModeGroupBox::SetEnableButtons(bool flag) {
    _send_btn->setEnabled(flag);
    _send_timer_btn->setEnabled(flag);
}//------------------------------------------------------------------


void TSendModeGroupBox::SetEnableButtons(bool flag) {
    _send_btn->setEnabled(flag);
    if (!CheckTimerSendingStatus())
        _send_timer_btn->setEnabled(flag && _correct_map->GetItemStatus(_timeout_ln_edit));
}//------------------------------------------------------------------


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
