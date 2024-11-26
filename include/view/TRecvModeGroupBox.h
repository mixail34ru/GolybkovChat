#ifndef TRECVMODEGROUPBOX_H
#define TRECVMODEGROUPBOX_H

#include "TUShortLineEdit.h"
#include "TURangeLineEdit.h"

#include <QGroupBox>
#include <QPushButton>
#include <QFormLayout>

class TModelStateInterface;

class TRecvModeGroupBox : public QGroupBox
{
    Q_OBJECT

    QFormLayout* _receive_frm_lt;
    TURangeLineEdit* _range_ln_edit;
    TUShortLineEdit* _port_ln_edit;
    QPushButton* _recv_btn;

public:
    TRecvModeGroupBox(TModelStateInterface* model, QWidget* parent = nullptr);
    ~TRecvModeGroupBox();

private slots:
    void setEnabled_recv_btn(bool flag);
    void setStatusReceivingPreset(bool flag);

signals:
    void receivePackageActivated(uint16_t max_pack, uint16_t port);

}; //class TRecvModeGroupBox
//-------------------------------------------------------------------

#endif // TRECVMODEGROUPBOX_H
