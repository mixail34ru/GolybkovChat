#ifndef TRECEIVERWIDGET_H
#define TRECEIVERWIDGET_H

#include <QWidget>

class TModelStateInterface;
class TRecvModeGroupBox;


class TReceiverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TReceiverWidget(
        TModelStateInterface* model, QWidget* parent = nullptr);
    ~TReceiverWidget();

signals:
    void receivePackageActivated(uint16_t max_pack, uint16_t port);
    void clearReceiveStorageActivated();

private:
    TRecvModeGroupBox* _mode_grp_bx;

}; //class TReceiverWidget
//-------------------------------------------------------------------

#endif // TRECEIVERWIDGET_H
