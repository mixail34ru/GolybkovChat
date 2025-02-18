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

<<<<<<< HEAD
    TCustomLineEdit* _ip_ln_edit;
    TCustomLineEdit* _port_ln_edit;
=======
    QLineEdit* _ip_ln_edit;
    QLineEdit* _port_ln_edit;
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

public:
    TSendNetGroupBox(QWidget* parent = nullptr);
    ~TSendNetGroupBox();

    std::optional<NetAddress> get_address();

    void SetEnableDataField(bool flag);

<<<<<<< HEAD
=======
private slots:
    void CorrectSignalEmitent(bool flag);
    void Validate_ip_ln_edit(const QString& text);
    void Validate_port_ln_edit(const QString& text);

>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
signals:
    void EnteredUncorrectParams(QObject* obj, bool flag);

}; //class TSendNetGroupBox
//-------------------------------------------------------------------

#endif // TSENDNETGROUPBOX_H
