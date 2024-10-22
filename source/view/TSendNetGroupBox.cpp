#include "TSendNetGroupBox.h"

#include <QFormLayout>

TSendNetGroupBox::TSendNetGroupBox(QWidget* parent) : QGroupBox(parent)
{
    /* Получатель посылки */

    _ip_ln_edit = new QLineEdit("192.168.16.10", this);
    _port_ln_edit = new QLineEdit("666", this);

    /* Настройка параметров виджета */

    QFormLayout* _net_frm_lt = new QFormLayout(this);
    _net_frm_lt->addRow("IPv4 адрес:", _ip_ln_edit);
    _net_frm_lt->addRow("Порт:", _port_ln_edit);

    this->setTitle("Получатель посылки");
    this->setLayout(_net_frm_lt);
}//------------------------------------------------------------------


TSendNetGroupBox::~TSendNetGroupBox() {
}//------------------------------------------------------------------


std::optional<NetAddress> TSendNetGroupBox::get_address() {
    try {
        NetAddress addr;
        addr.port = _port_ln_edit->text().toUShort();
        addr.ip = _ip_ln_edit->text().toStdString();

        return addr;
    }
    catch (...) {

    }

    return std::nullopt;
}//------------------------------------------------------------------
