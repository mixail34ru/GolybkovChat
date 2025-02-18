#include "TRecvModeGroupBox.h"
<<<<<<< HEAD
#include "TCustomLineEdit.h"
#include "TUShortValidator.h"
=======

>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
#include "TModelStateInterface.h"

#include <QHBoxLayout>
#include <QLabel>

TRecvModeGroupBox::TRecvModeGroupBox(TModelStateInterface* model, QWidget* parent)
    : QGroupBox(parent)
{
<<<<<<< HEAD
    QHBoxLayout* form_hlt = new QHBoxLayout(this);

    _port_ln_edit = new TCustomLineEdit(new TUShortValidator(this), "666", this);
    _port_ln_edit->setFocusPolicy(Qt::ClickFocus);
=======
    QHBoxLayout* port_hlt = new QHBoxLayout(this);

    port_hlt->addWidget(new QLabel("Порт:"));

    _port_ln_edit = new TUShortLineEdit("666", this);
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    connect(
        _port_ln_edit, SIGNAL(EnteredCorrectParams(bool)),
        this, SLOT(setEnabled_recv_btn(bool))
    );
<<<<<<< HEAD
    connect(
        _port_ln_edit, &QLineEdit::editingFinished,
        [this]() { _port_ln_edit->delete_Null();}
    );

    _range_ln_edit = new TCustomLineEdit(new TUShortValidator(1, 300, this), "1", this);
    _range_ln_edit->setFocusPolicy(Qt::ClickFocus);
    connect(
        _range_ln_edit, &TCustomLineEdit::EnteredCorrectParams,
        this, &TRecvModeGroupBox::setEnabled_recv_btn
    );
    connect(
        _range_ln_edit, &QLineEdit::editingFinished,
        [this]() { _range_ln_edit->delete_Null();}
    );
=======
    port_hlt->addWidget(_port_ln_edit);
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

    _recv_btn = new QPushButton("Запустить прослушку");
    connect(_recv_btn, &QPushButton::clicked,
        [this](bool flag) {
            setEnabled_recv_btn(false);
<<<<<<< HEAD
            emit receivePackageActivated(
                _range_ln_edit->text().toUShort(), _port_ln_edit->text().toUShort()
            );
        }
    );

    _clear_btn = new QPushButton("Очистить таблицу");
    connect(
        _clear_btn, &QPushButton::clicked,
        this, &TRecvModeGroupBox::clearReceiveStorageActivated
    );

    connect(
        model, &TModelStateInterface::statusReceivingChanged,
        this, &TRecvModeGroupBox::setStatusReceivingPreset
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

=======
            emit receivePackageActivated(_port_ln_edit->text().toUShort());
        }
    );
    connect(
        model, SIGNAL(statusReceivingChanged(bool)),
        this, SLOT(setStatusReceivingPreset(bool))
    );
    port_hlt->addWidget(_recv_btn);

    /* Настройка параметров виджета */

    this->setTitle("Режим прослушивания");
    this->setLayout(port_hlt);
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
}//------------------------------------------------------------------


TRecvModeGroupBox::~TRecvModeGroupBox() {
}//------------------------------------------------------------------


void TRecvModeGroupBox::setEnabled_recv_btn(bool flag) {
<<<<<<< HEAD
    if(_port_ln_edit->getCorrect() && _range_ln_edit->getCorrect()) flag = true;
    else flag = false;
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    _recv_btn->setEnabled(flag);
}//------------------------------------------------------------------


void TRecvModeGroupBox::setStatusReceivingPreset(bool flag) {
    if (flag) {
        _port_ln_edit->setEnabled(false);
<<<<<<< HEAD
        _range_ln_edit->setEnabled(false);
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
        _recv_btn->setText("Остановить прослушку");
        _recv_btn->setEnabled(true);
    }
    else {
        _port_ln_edit->setEnabled(true);
<<<<<<< HEAD
        _range_ln_edit->setEnabled(true);
        _recv_btn->setText("Запустить прослушку");

        if (_port_ln_edit->getCorrect() && _range_ln_edit->getCorrect())
            _recv_btn->setEnabled(true);
        else
            _recv_btn->setEnabled(false);
=======
        _recv_btn->setText("Запустить прослушку");

        if (_port_ln_edit->isCorrect()) _recv_btn->setEnabled(true);
        else                            _recv_btn->setEnabled(false);
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    }
}//------------------------------------------------------------------
