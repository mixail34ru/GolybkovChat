#ifndef TSENDMODEGROUPBOX_H
#define TSENDMODEGROUPBOX_H

#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include <functional>

class TModelStateInterface;

class TSendModeGroupBox : public QGroupBox
{
    Q_OBJECT

    QFormLayout* _send_frm_lt;
    QComboBox* _mode_cmb_bx;
    QLineEdit* _timeout_ln_edit;
    QPushButton* _send_timer_btn;
    QPushButton* _send_btn;

    std::function<bool(void)> CheckSendingStatus;

public:
    TSendModeGroupBox(TModelStateInterface* model, QWidget* parent = nullptr);
    ~TSendModeGroupBox();

private slots:
    void SetCurrentMode(int index);
    void SetStatus_send_timer_btn(bool);
    void SetStatus_send_btn(bool);

signals:
    void send_activated();
    void send_timer_activated(uint timeout);

}; //class TSendModeGroupBox
//-------------------------------------------------------------------

#endif // TSENDMODEGROUPBOX_H
