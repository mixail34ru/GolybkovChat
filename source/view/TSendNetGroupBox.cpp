#include "TSendNetGroupBox.h"
#include "TUShortValidator.h"
#include "TIPValidator.h"

#include "TCorrectItemMap.h"

#include <QFormLayout>
#include <QRegularExpressionValidator>

TSendNetGroupBox::TSendNetGroupBox(QWidget* parent)
    : QGroupBox(parent)
{
    _correct_map = new TCorrectItemMap(this);
    connect(
        _correct_map, &TCorrectItemMap::CorrectStatusChanged,
        [this] (auto arg) { emit EnteredUncorrectParams(this, arg); }
    );

    /* IPv4 адрес */

    _ip_ln_edit = new TCustomLineEdit(new TIPValidator(this), "192.168.16.96", this);
    _correct_map->EmplaceItem(_ip_ln_edit, true);
    connect(
        _ip_ln_edit, &TCustomLineEdit::EnteredCorrectParams,
        [this](auto arg) { _correct_map->SetItemStatus(_ip_ln_edit, arg);}
    );

    /* Порт */

    _port_ln_edit = new TCustomLineEdit(new TUShortValidator(this), "666", this);
    _correct_map->EmplaceItem(_port_ln_edit, true);
    connect(
        _port_ln_edit, &TCustomLineEdit::EnteredCorrectParams,
        [this](auto arg) { _correct_map->SetItemStatus(_port_ln_edit, arg);}
    );
    connect(
        _port_ln_edit, &QLineEdit::editingFinished,
        [this]() { _port_ln_edit->delete_Null();}
    );

    /* Настройка параметров виджета */

    QFormLayout* _net_frm_lt = new QFormLayout(this);
    _net_frm_lt->addRow("IPv4 адрес:", _ip_ln_edit);
    _net_frm_lt->addRow("Порт:", _port_ln_edit);

    this->setTitle("Получатель посылки");
    this->setLayout(_net_frm_lt);
}//------------------------------------------------------------------


TSendNetGroupBox::~TSendNetGroupBox() {
}//------------------------------------------------------------------


QString DropZero(const QString& text) {
    static QRegularExpression regexp("(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})");
    QRegularExpressionMatch match = regexp.match(text);

    if (match.hasMatch()) {
        QStringList list = match.capturedTexts();
        QString str =
            QString::number(list.at(1).toInt()) + "." +
            QString::number(list.at(2).toInt()) + "." +
            QString::number(list.at(3).toInt()) + "." +
            QString::number(list.at(4).toInt());

        return str;
    }

    return text;
}//------------------------------------------------------------------


std::optional<NetAddress> TSendNetGroupBox::get_address() {
    try {
        // Удаление нолей перед значащими символами
        _ip_ln_edit->setText(DropZero(_ip_ln_edit->text()));

        NetAddress addr;
        addr.port = _port_ln_edit->text().toUShort();
        addr.ip = _ip_ln_edit->text().toStdString();

        return addr;
    }
    catch (...) {

    }

    return std::nullopt;
}//------------------------------------------------------------------


void TSendNetGroupBox::SetEnableDataField(bool flag) {
    _ip_ln_edit->setEnabled(flag);
    _port_ln_edit->setEnabled(flag);
}//------------------------------------------------------------------
