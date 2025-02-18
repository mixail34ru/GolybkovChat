#ifndef TSENDNETGROUPBOX_H
#define TSENDNETGROUPBOX_H

#include "TPackageFormat.h"

#include "TCustomLineEdit.h"

#include <QGroupBox>
#include <QLineEdit>

class TCorrectItemMap;

class TSendNetGroupBox : public QGroupBox
{
    Q_OBJECT

    TCorrectItemMap* _correct_map;

    TCustomLineEdit* _ip_ln_edit;
    TCustomLineEdit* _port_ln_edit;

public:
    TSendNetGroupBox(QWidget* parent = nullptr);
    ~TSendNetGroupBox();

    std::optional<NetAddress> get_address();

    void SetEnableDataField(bool flag);

signals:
    void EnteredUncorrectParams(QObject* obj, bool flag);

}; //class TSendNetGroupBox
//-------------------------------------------------------------------

#endif // TSENDNETGROUPBOX_H
