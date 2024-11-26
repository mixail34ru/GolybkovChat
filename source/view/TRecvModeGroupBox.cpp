#include "TRecvModeGroupBox.h"

#include "TModelStateInterface.h"

#include <QHBoxLayout>
#include <QLabel>

TRecvModeGroupBox::TRecvModeGroupBox(TModelStateInterface* model, QWidget* parent)
    : QGroupBox(parent)
{
    QHBoxLayout* form_hlt = new QHBoxLayout(this);

    _port_ln_edit = new TUShortLineEdit("666", this);
    connect(
        _port_ln_edit, SIGNAL(EnteredCorrectParams(bool)),
        this, SLOT(setEnabled_recv_btn(bool))
    );

    //TURangeLineEdit::Range range{1,300};
    _range_ln_edit = new TURangeLineEdit("1", TURangeLineEdit::Range{1, 300}, this);
    //_range_ln_edit = new TURangeLineEdit("1", 1, 300, this);
    connect(
        _range_ln_edit, SIGNAL(EnteredCorrectParams(bool)),
        this, SLOT(setEnabled_recv_btn(bool))
        );

    _recv_btn = new QPushButton("Запустить прослушку");
    connect(_recv_btn, &QPushButton::clicked,
        [this](bool flag) {
            setEnabled_recv_btn(false);
            emit receivePackageActivated(_range_ln_edit->text().toUShort(), _port_ln_edit->text().toUShort());
        }
    );

    connect(
        model, SIGNAL(statusReceivingChanged(bool)),
        this, SLOT(setStatusReceivingPreset(bool))
    );

    /* Настройка параметров виджета */

    _recv_btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

    _receive_frm_lt = new QFormLayout(this);
    _receive_frm_lt->addRow("Порт", _port_ln_edit);
    _receive_frm_lt->addRow("Макс. кол-во пакетов", _range_ln_edit);

    form_hlt->addLayout(_receive_frm_lt);
    form_hlt->addWidget(_recv_btn);

    this->setTitle("Режим прослушивания");
    this->setLayout(_receive_frm_lt);

}//------------------------------------------------------------------


TRecvModeGroupBox::~TRecvModeGroupBox() {
}//------------------------------------------------------------------


void TRecvModeGroupBox::setEnabled_recv_btn(bool flag) {
    if(_port_ln_edit->isCorrect() && _range_ln_edit->isCorrect()) flag = true;
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

        if (_port_ln_edit->isCorrect() && _range_ln_edit->isCorrect()) _recv_btn->setEnabled(true);
        else                            _recv_btn->setEnabled(false);
    }
}//------------------------------------------------------------------
