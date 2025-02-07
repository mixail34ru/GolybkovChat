#include "TRecvModeGroupBox.h"
#include "TUShortValidator.h"

#include "TModelStateInterface.h"

#include <QHBoxLayout>
#include <QLabel>

TRecvModeGroupBox::TRecvModeGroupBox(TModelStateInterface* model, QWidget* parent)
    : QGroupBox(parent)
{
    QHBoxLayout* form_hlt = new QHBoxLayout(this);

    _port_ln_edit = new TCustomLineEdit(new TUShortValidator(this), "666", this);
    connect(
        _port_ln_edit, SIGNAL(EnteredCorrectParams(bool)),
        this, SLOT(setEnabled_recv_btn(bool))
    );
    connect(
        _port_ln_edit, &QLineEdit::editingFinished,
        [this]() { _port_ln_edit->delete_Null();}
        );

    _range_ln_edit = new TCustomLineEdit(new TUShortValidator(1, 300, this), "1", this);
    connect(
        _range_ln_edit, SIGNAL(EnteredCorrectParams(bool)),
        this, SLOT(setEnabled_recv_btn(bool))
        );
    connect(
        _range_ln_edit, &QLineEdit::editingFinished,
        [this]() { _range_ln_edit->delete_Null();}
        );

    _recv_btn = new QPushButton("Запустить прослушку");
    connect(_recv_btn, &QPushButton::clicked,
        [this](bool flag) {
            setEnabled_recv_btn(false);
            emit receivePackageActivated(
                _range_ln_edit->text().toUShort(), _port_ln_edit->text().toUShort()
            );
        }
    );

    _clear_btn = new QPushButton("Очистить таблицу");
    connect(
        _clear_btn, &QPushButton::clicked,
        [model]() {emit model->tableClear();}
    );

    connect(
        model, SIGNAL(statusReceivingChanged(bool)),
        this, SLOT(setStatusReceivingPreset(bool))
    );

    /* Настройка параметров виджета */

    _receive_frm_lt = new QFormLayout();
    _receive_frm_lt->addRow("Порт:", _port_ln_edit);
    _receive_frm_lt->addRow("Макс. кол-во пакетов:", _range_ln_edit);

    _button_frm_lt = new QVBoxLayout();
    _button_frm_lt->addWidget(_recv_btn);
    _button_frm_lt->addWidget(_clear_btn);

    form_hlt->addLayout(_receive_frm_lt);
    form_hlt->addLayout(_button_frm_lt);

    this->setTitle("Режим прослушивания");
    this->setLayout(form_hlt);

}//------------------------------------------------------------------


TRecvModeGroupBox::~TRecvModeGroupBox() {
}//------------------------------------------------------------------


void TRecvModeGroupBox::setEnabled_recv_btn(bool flag) {
    if(_port_ln_edit->getCorrect() && _range_ln_edit->getCorrect()) flag = true;
    else flag = false;
    _recv_btn->setEnabled(flag);
}//------------------------------------------------------------------


void TRecvModeGroupBox::setStatusReceivingPreset(bool flag) {
    if (flag) {
        _port_ln_edit->setEnabled(false);
        _range_ln_edit->setEnabled(false);
        _recv_btn->setText("Остановить прослушку");
        _recv_btn->setEnabled(true);
    }
    else {
        _port_ln_edit->setEnabled(true);
        _range_ln_edit->setEnabled(true);
        _recv_btn->setText("Запустить прослушку");

        if (_port_ln_edit->getCorrect() && _range_ln_edit->getCorrect()) _recv_btn->setEnabled(true);
        else                            _recv_btn->setEnabled(false);
    }
}//------------------------------------------------------------------
