#ifndef TRECVMODEGROUPBOX_H
#define TRECVMODEGROUPBOX_H

#include "TUShortLineEdit.h"
#include "TURangeLineEdit.h"
#include "TCustomLineEdit.h"

#include <QGroupBox>
#include <QPushButton>
#include <QFormLayout>

class TModelStateInterface;

class TRecvModeGroupBox : public QGroupBox
{
    Q_OBJECT

    QVBoxLayout* _button_frm_lt;
    QFormLayout* _receive_frm_lt;

    TCustomLineEdit* _range_ln_edit;
    TCustomLineEdit* _port_ln_edit;

    QPushButton* _recv_btn;
    QPushButton* _clear_btn;

public:
    TRecvModeGroupBox(TModelStateInterface* model, QWidget* parent = nullptr);
    ~TRecvModeGroupBox();

private slots:
    void setEnabled_recv_btn(bool flag);
    void setStatusReceivingPreset(bool flag);

signals:
    void receivePackageActivated(uint16_t max_pack, uint16_t port);
    //void storageClear();

}; //class TRecvModeGroupBox
//-------------------------------------------------------------------

#endif // TRECVMODEGROUPBOX_H
