#ifndef TSENDNETGROUPBOX_H
#define TSENDNETGROUPBOX_H

#include "TPackageFormat.h"

#include <QGroupBox>
#include <QLineEdit>

class TCorrectItemMap;

class TSendNetGroupBox : public QGroupBox
{
    Q_OBJECT

    TCorrectItemMap* _correct_map;

    QLineEdit* _ip_ln_edit;
    QLineEdit* _port_ln_edit;

public:
    TSendNetGroupBox(QWidget* parent = nullptr);
    ~TSendNetGroupBox();

    std::optional<NetAddress> get_address();

    void SetEnableDataField(bool flag);

private slots:
    void CorrectSignalEmitent(bool flag);
    void Validate_ip_ln_edit(const QString& text);
    void Validate_port_ln_edit(const QString& text);

signals:
    void EnteredUncorrectParams(QObject* obj, bool flag);

}; //class TSendNetGroupBox
//-------------------------------------------------------------------

#endif // TSENDNETGROUPBOX_H
