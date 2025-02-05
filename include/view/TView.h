#ifndef TVIEW_H
#define TVIEW_H

#include "TPackageFormat.h"

#include <QObject>
#include <memory>

class TModelStateInterface;

class TView : public QObject
{
    Q_OBJECT

public:
    TView(TModelStateInterface *model, QObject *parent = nullptr);

    TView(const TView& rhs) = delete;
    TView& operator=(const TView& rhs) = delete;

    TView(TView&& rhs) noexcept = delete;
    TView& operator=(TView&& rhs) noexcept = delete;

    ~TView();

    void run();

signals:
    void sendActivated(ViewSendInfo info);
    void sendTimerActivated(uint timeout, ViewSendInfo info);
    void receiveActivated(uint16_t max_pack, uint16_t port);

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;

}; //class TView
//-------------------------------------------------------------------

#endif // TVIEW_H
