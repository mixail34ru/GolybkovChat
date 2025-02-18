#ifndef TRECVMODEGROUPBOX_H
#define TRECVMODEGROUPBOX_H

<<<<<<< HEAD
#include <QGroupBox>
#include <QPushButton>
#include <QFormLayout>

class TModelStateInterface;
class TCustomLineEdit;

=======
#include "TUShortLineEdit.h"

#include <QGroupBox>
#include <QPushButton>

class TModelStateInterface;
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

class TRecvModeGroupBox : public QGroupBox
{
    Q_OBJECT

<<<<<<< HEAD
public:
    explicit TRecvModeGroupBox(
        TModelStateInterface* model, QWidget* parent = nullptr);
    ~TRecvModeGroupBox();

signals:
    void receivePackageActivated(uint16_t max_pack, uint16_t port);
    void clearReceiveStorageActivated();

private:
    QVBoxLayout* _button_frm_lt;
    QFormLayout* _receive_frm_lt;

    TCustomLineEdit* _range_ln_edit;
    TCustomLineEdit* _port_ln_edit;

    QPushButton* _recv_btn;
    QPushButton* _clear_btn;
=======
    TUShortLineEdit* _port_ln_edit;
    QPushButton* _recv_btn;

public:
    TRecvModeGroupBox(TModelStateInterface* model, QWidget* parent = nullptr);
    ~TRecvModeGroupBox();
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

private slots:
    void setEnabled_recv_btn(bool flag);
    void setStatusReceivingPreset(bool flag);

<<<<<<< HEAD
=======
signals:
    void receivePackageActivated(uint16_t port);

>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
}; //class TRecvModeGroupBox
//-------------------------------------------------------------------

#endif // TRECVMODEGROUPBOX_H
