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
#include <QItemSelectionModel>

#include <QDebug>

#include <algorithm>

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


    TSendParcelTableModel* _parcel_model = new TSendParcelTableModel(model);


    QSortFilterProxyModel* _proxy_model = new QSortFilterProxyModel();
    _proxy_model->setSourceModel(_parcel_model);

    QItemSelectionModel* _selection_model = new QItemSelectionModel(_proxy_model);

    TSendParcelTableView* _parcel_table = new TSendParcelTableView(nullptr);
    _parcel_table->setModel(_proxy_model);
    _parcel_table->setSelectionModel(_selection_model);

    QPushButton* _sort_btn = new QPushButton("Вернуть исходный порядок");
    q->connect(_sort_btn, &QPushButton::clicked,
        [=] () {
            _proxy_model->sort(-1,Qt::AscendingOrder);
        }
        );

    //_parcel_table->select

    q->connect(_selection_model, &QItemSelectionModel::currentChanged,
       [=](const QModelIndex &current, const QModelIndex &previous) {
           //auto list = _selection_model->selectedIndexes();
           //int size = list.size();
    }
    );

    QPushButton* _del_btn = new QPushButton("Удалить пакет");
    _del_btn->setEnabled(false);

    q->connect(_selection_model, &QItemSelectionModel::selectionChanged,
        [=](const QItemSelection &selected, const QItemSelection &deselected) {
            //auto list = _selection_model->selectedIndexes();
            //int size = list.size();
            _list = _selection_model->selectedRows();
            if (_list.count() > 0)
                _del_btn->setEnabled(true);
            else
                _del_btn->setEnabled(false);
        }
    );

    //QPushButton* _del_btn = new QPushButton("Удалить пакет");
    q->connect(
        _del_btn, &QPushButton::clicked, [=](bool checked) {
            //_selection_model->selectedRows()
            //QModelIndexList list = _selection_model->selectedRows();

            std::sort(_list.begin(), _list.end(),
                [this](auto& v1, auto& v2) { return v1.row() > v2.row(); });

            for (auto& it : _list) {
                if (it.isValid()) {
                    QModelIndex index = _proxy_model->mapToSource(it);
                    qDebug() << "ListIndex: deleted row index = " << index.row();

                    emit q->delSendPackageActivated(index.row());

                    //_parcel_table->setCurrentIndex(QModelIndex());
                }
            }

            // auto list = _selection_model->selectedIndexes();
            // int size = list.size();

            // auto index = _selection_model->currentIndex();
            // if (index.isValid()) {
            //     qDebug() << "selection_model index = " << index.row();
            // }

            //_selection_model->

            // auto pindex = _parcel_table->currentIndex();

            // if (pindex.isValid()) { // Поиск истинного индекса
            //     auto mindex = _proxy_model->mapToSource(pindex);

            //     qDebug() << "ProxyIndex: row = " << pindex.row() << "\t"
            //              << "ModelIndex: row = " << mindex.row();

            //     emit q->delSendPackageActivated(mindex.row());

            //     _parcel_table->setCurrentIndex(QModelIndex());
            // }
        }
    );

    QPushButton* _clean_btn = new QPushButton("Очистить посылку");
    _clean_btn->setEnabled(false);
    q->connect(
        _clean_btn, &QPushButton::clicked,
        //q, &TParcelWindow::clearSendStorageActivated
        [=](){
            _clean_btn->setEnabled(false);
            _del_btn->setEnabled(false);
            emit q->clearSendStorageActivated();
        }
    );

    q->connect(
        _parcel_model, &TSendParcelTableModel::rowsRemoved,
        [=](const QModelIndex &parent, int first, int last)
        {
            if(_parcel_model->rowCount() > 0){
                _clean_btn->setEnabled(true);
            }
            else{
                _clean_btn->setEnabled(false);
            }
        }
    );
    q->connect(
        _parcel_model, &TSendParcelTableModel::rowsInserted,
        [=](const QModelIndex &parent, int first, int last)
        {
            if(_parcel_model->rowCount() > 0){
                _clean_btn->setEnabled(true);
            }
            else{
                _clean_btn->setEnabled(false);
            }
        }
    );


    QHBoxLayout* remove_hlt = new QHBoxLayout();
    remove_hlt->addWidget(_del_btn);
    remove_hlt->addWidget(_clean_btn);
     remove_hlt->addWidget(_sort_btn);
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

