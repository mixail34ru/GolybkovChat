#ifndef TSENDMODEGROUPBOX_H
#define TSENDMODEGROUPBOX_H

#include <QGroupBox>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include <functional>

class TModelStateInterface;
class TCorrectItemMap;

class TSendModeGroupBox : public QGroupBox
{
    Q_OBJECT

    std::function<bool(void)> CheckTimerSendingStatus;

    TCorrectItemMap* _correct_map;

    QFormLayout* _send_frm_lt;
    QComboBox* _mode_cmb_bx;
    QLineEdit* _timeout_ln_edit;
    QLineEdit* _pack_ln_edit;
    QPushButton* _send_timer_btn;
    QPushButton* _send_btn;

public:
    TSendModeGroupBox(TModelStateInterface* model, QWidget* parent = nullptr);
    ~TSendModeGroupBox();

    void SetEnableButtons(bool flag);

private slots:
    void setCurrentMode(int index);
    void setStatus_send_timer_btn(bool flag);
    void setStatus_send_btn(bool flag);
    void check_pack_ln_edit(const QString& text);
    void check_timeout_ln_edit(const QString& text);

signals:
    void sendActivated(uint num_pack);
    void sendTimerActivated(uint timeout, uint num_pack);

}; //class TSendModeGroupBox
//-------------------------------------------------------------------

#endif // TSENDMODEGROUPBOX_H
