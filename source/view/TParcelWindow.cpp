#include "TParcelWindow.h"
#include "TParcelWindow_p.h"

#include "TSendDataGroupBox.h"
#include "TSendParcelTableView.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>

/********************************************************************
 **********************  TParcelWindowPrivate  **********************
 *******************************************************************/

TParcelWindow::TParcelWindowPrivate::TParcelWindowPrivate() {
}//------------------------------------------------------------------


TParcelWindow::TParcelWindowPrivate::~TParcelWindowPrivate() {
}//------------------------------------------------------------------


/********************************************************************
 ************************   TParcelWindow   *************************
 *******************************************************************/


TParcelWindow::TParcelWindow(QWidget *parent)
    : QWidget(parent), d_ptr(new TParcelWindowPrivate())
{
    Q_D(TParcelWindow);
    d->q_ptr = this;

    /* Компоновка раздела "Добавить пакет" */

    TSendDataGroupBox* _send_data_gb = new TSendDataGroupBox();

    QVBoxLayout* add_vlt = new QVBoxLayout();
    add_vlt->addWidget(_send_data_gb);
    add_vlt->addStretch(1);

    /* Компоновка раздела "Просмотр пакетов" */

    TSendParcelTableView* _parcel_table = new TSendParcelTableView(nullptr, this);

    QPushButton* del_btn = new QPushButton("Удалить пакет", this);
    QPushButton* clern_btn = new QPushButton("Очистить посылку", this);

    QHBoxLayout* remove_hlt = new QHBoxLayout();
    remove_hlt->addWidget(del_btn);
    remove_hlt->addWidget(clern_btn);
    remove_hlt->addStretch(1);

    QVBoxLayout* remove_vlt = new QVBoxLayout();
    remove_vlt->addWidget(new QLabel("Содержимое отправляемой посылки:"));
    remove_vlt->addWidget(_parcel_table);
    remove_vlt->addLayout(remove_hlt);

    /* Настройка взаимодействия разделов */

    QHBoxLayout* all_hlt = new QHBoxLayout();
    all_hlt->addLayout(add_vlt, false);
    all_hlt->addLayout(remove_vlt, true);

    this->setLayout(all_hlt);
    this->setWindowTitle("Редактор отправляемой посылки");

}//------------------------------------------------------------------


TParcelWindow::~TParcelWindow() {
}//------------------------------------------------------------------


TParcelWindow::TParcelWindow(TParcelWindowPrivate &dd, QWidget *parent)
    : QWidget(parent), d_ptr(&dd)
{
    Q_D(TParcelWindow);
    d->q_ptr = this;
}//------------------------------------------------------------------
