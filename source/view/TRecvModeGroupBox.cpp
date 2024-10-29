#include "TRecvModeGroupBox.h"

#include "TModelStateInterface.h"

#include <QHBoxLayout>
#include <QLabel>

TRecvModeGroupBox::TRecvModeGroupBox(TModelStateInterface* model, QWidget* parent)
    : QGroupBox(parent)
{
    QHBoxLayout* port_hlt = new QHBoxLayout(this);

    port_hlt->addWidget(new QLabel("Порт:"));

    _port_ln_edit = new TUShortLineEdit("666", this);
    connect(
        _port_ln_edit, SIGNAL(EnteredCorrectParams(bool)),
        this, SLOT(setEnabled_recv_btn(bool))
    );
    port_hlt->addWidget(_port_ln_edit);

    _recv_btn = new QPushButton("Запустить прослушку");
    connect(_recv_btn, &QPushButton::clicked,
        [this](bool flag) {
            setEnabled_recv_btn(false);
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
}//------------------------------------------------------------------


TRecvModeGroupBox::~TRecvModeGroupBox() {
}//------------------------------------------------------------------


void TRecvModeGroupBox::setEnabled_recv_btn(bool flag) {
    _recv_btn->setEnabled(flag);
}//------------------------------------------------------------------


void TRecvModeGroupBox::setStatusReceivingPreset(bool flag) {
    if (flag) {
        _port_ln_edit->setEnabled(false);
        _recv_btn->setText("Остановить прослушку");
        _recv_btn->setEnabled(true);
    }
    else {
        _port_ln_edit->setEnabled(true);
        _recv_btn->setText("Запустить прослушку");

        if (_port_ln_edit->isCorrect()) _recv_btn->setEnabled(true);
        else                            _recv_btn->setEnabled(false);
    }
}//------------------------------------------------------------------
