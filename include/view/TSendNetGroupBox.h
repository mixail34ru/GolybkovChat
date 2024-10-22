#ifndef TSENDNETGROUPBOX_H
#define TSENDNETGROUPBOX_H

#include "TPackageFormat.h"

#include <QGroupBox>
#include <QLineEdit>

class TSendNetGroupBox : public QGroupBox
{
    Q_OBJECT

    QLineEdit* _ip_ln_edit;
    QLineEdit* _port_ln_edit;

public:
    TSendNetGroupBox(QWidget* parent = nullptr);
    ~TSendNetGroupBox();

    std::optional<NetAddress> get_address();

}; //class TSendNetGroupBox
//-------------------------------------------------------------------

#endif // TSENDNETGROUPBOX_H
