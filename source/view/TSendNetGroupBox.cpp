#include "TSendNetGroupBox.h"

#include "TCorrectItemMap.h"

#include <QFormLayout>
#include <QRegularExpressionValidator>


QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
QRegularExpression ip_regexp("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");


TSendNetGroupBox::TSendNetGroupBox(QWidget* parent)
    : QGroupBox(parent)
{
    _correct_map = new TCorrectItemMap(this);
    connect(
        _correct_map, SIGNAL(CorrectStatusChanged(bool)),
        this, SLOT(CorrectSignalEmitent(bool))
    );

    /* IPv4 адрес */

    _ip_ln_edit = new QLineEdit("192.168.16.10", this);
    _correct_map->EmplaceItem(_ip_ln_edit, true);
    _ip_ln_edit->setValidator(
        new QRegularExpressionValidator(ip_regexp, this)
    );
    connect(
        _ip_ln_edit, SIGNAL(textChanged(QString)),
        this, SLOT(Validate_ip_ln_edit(QString))
    );

    /* Порт */

    _port_ln_edit = new QLineEdit("666", this);
    _correct_map->EmplaceItem(_port_ln_edit, true);
    _port_ln_edit->setValidator(
        new QIntValidator(0, USHRT_MAX, _port_ln_edit)
    );
    connect(
        _port_ln_edit, SIGNAL(textChanged(QString)),
        this, SLOT(Validate_port_ln_edit(QString))
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


/* private slots: */

void TSendNetGroupBox::CorrectSignalEmitent(bool flag) {
    emit EnteredUncorrectParams(this, flag);
}//------------------------------------------------------------------


void TSendNetGroupBox::Validate_ip_ln_edit(const QString& text) {
    QRegularExpressionMatch match = ip_regexp.match(text);
    if (match.hasMatch()) {
        _ip_ln_edit->setStyleSheet("QLineEdit { color: black }");
        _correct_map->SetItemStatus(_ip_ln_edit, true);
    }
    else {
        _ip_ln_edit->setStyleSheet("QLineEdit { color: red }");
        _correct_map->SetItemStatus(_ip_ln_edit, false);
    }
}//------------------------------------------------------------------


void TSendNetGroupBox::Validate_port_ln_edit(const QString& text) {
    uint32_t num = text.toUInt();
    if (num >= 0 && num <= USHRT_MAX) {
        _port_ln_edit->setStyleSheet("QLineEdit { color: black }");
        _correct_map->SetItemStatus(_port_ln_edit, true);

    }
    else {
        _port_ln_edit->setStyleSheet("QLineEdit { color: red }");
        _correct_map->SetItemStatus(_port_ln_edit, false);
    }
}//------------------------------------------------------------------
