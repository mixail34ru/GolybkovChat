#include "TParcelWindow.h"
#include "TParcelWindow_p.h"

#include "TModelStateInterface.h"

#include "TSendDataGroupBox.h"
#include "TSendParcelTableModel.h"
#include "TSendParcelTableView.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QSortFilterProxyModel>

#include <QDebug>

/********************************************************************
 **********************  TParcelWindowPrivate  **********************
 *******************************************************************/

TParcelWindowPrivate::TParcelWindowPrivate(
    TModelStateInterface* model, TParcelWindow* qq)
    : q_ptr(qq)
{
    Q_Q(TParcelWindow);

    /* Компоновка раздела "Добавить пакет" */

    TSendDataGroupBox* send_data_gb = new TSendDataGroupBox();
    q->connect(
        send_data_gb, &TSendDataGroupBox::addPackageActivated,
        q, &TParcelWindow::addSendPackageActivated
    );

    QVBoxLayout* add_vlt = new QVBoxLayout();
    add_vlt->addWidget(send_data_gb);
    add_vlt->addStretch(1);

    /* Компоновка раздела "Просмотр пакетов" */

    //TSendParcelTableModel* _parcel_model = new TSendParcelTableModel(model);
    //TSendParcelTableView* _parcel_table = new TSendParcelTableView(_parcel_model);

    TSendParcelTableView* _parcel_table = new TSendParcelTableView(nullptr);
    TSendParcelTableModel* _parcel_model = new TSendParcelTableModel(model);
    QSortFilterProxyModel* _proxy_model = new QSortFilterProxyModel();

    _proxy_model->setSourceModel(_parcel_model);
    _parcel_table->setModel(_proxy_model);

    QPushButton* _del_btn = new QPushButton("Удалить пакет");
    q->connect(
        _del_btn, &QPushButton::clicked,
        [q, _parcel_table, _proxy_model](bool checked) {
            auto pindex = _parcel_table->currentIndex();

            if (pindex.isValid()) { // Поиск истинного индекса
                auto mindex = _proxy_model->mapToSource(pindex);

                qDebug() << "ProxyIndex: row = " << pindex.row() << "\t"
                         << "ModelIndex: row = " << mindex.row();

                emit q->delSendPackageActivated(mindex.row());

                _parcel_table->setCurrentIndex(QModelIndex());
            }
        }
    );

    QPushButton* _clean_btn = new QPushButton("Очистить посылку");
    q->connect(
        _clean_btn, &QPushButton::clicked,
        q, &TParcelWindow::clearSendStorageActivated
    );

    QHBoxLayout* remove_hlt = new QHBoxLayout();
    remove_hlt->addWidget(_del_btn);
    remove_hlt->addWidget(_clean_btn);
    remove_hlt->addStretch(1);

    QVBoxLayout* remove_vlt = new QVBoxLayout();
    remove_vlt->addWidget(new QLabel("Содержимое отправляемой посылки:"));
    remove_vlt->addWidget(_parcel_table);
    remove_vlt->addLayout(remove_hlt);

    /* Настройка взаимодействия разделов */

    QHBoxLayout* all_hlt = new QHBoxLayout();
    all_hlt->addLayout(add_vlt, false);
    all_hlt->addLayout(remove_vlt, true);

    q->setLayout(all_hlt);
    q->setWindowTitle("Редактор отправляемой посылки");

}//------------------------------------------------------------------


TParcelWindowPrivate::~TParcelWindowPrivate() {
}//------------------------------------------------------------------


/********************************************************************
 ************************   TParcelWindow   *************************
 *******************************************************************/


TParcelWindow::TParcelWindow(TModelStateInterface* model, QWidget *parent)
    : QWidget(parent), d_ptr(new TParcelWindowPrivate(model, this))
{}//-----------------------------------------------------------------


TParcelWindow::~TParcelWindow() {
}//------------------------------------------------------------------


TParcelWindow::TParcelWindow(TParcelWindowPrivate &dd)
    : d_ptr(&dd)
{}//-----------------------------------------------------------------
