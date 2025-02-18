#include "TSendParcelTableModel.h"
#include "TModelStateInterface.h"


TSendParcelTableModel::TSendParcelTableModel(
    TModelStateInterface* model, QObject* parent)
    : QAbstractTableModel(parent), _model(model), _count_row(0)
{
    // connect(_model, &TModelStateInterface::sendStorageChanged,
    //         this, &TSendParcelTableModel::addDataRow);

    // connect(
    //     _model, &TModelStateInterface::sendStorageChanged,
    //     [this](){
    //         insertRows(
    //             rowCount(QModelIndex()),
    //             _model->getSendStorage().size() - 1,
    //             QModelIndex()
    //         );
    //     });

    // connect(_model, &TModelStateInterface::sendStorageCleared,
    //         this, &TSendParcelTableModel::clearTable);


    connect(_model, &TModelStateInterface::sendStorageInserted,
            [this](int row, int count) { insertRows(row, count); });

    connect(_model, &TModelStateInterface::sendStorageErased,
            [this](int row, int count) { removeRows(row, count); });

    connect(_model, &TModelStateInterface::sendStorageCleared,
            [this]() { beginResetModel(); endResetModel(); });

    headersFormer();
}//------------------------------------------------------------------


TSendParcelTableModel::~TSendParcelTableModel() {
}//------------------------------------------------------------------


// bool TSendParcelTableModel::hasIndex(
//     int row, int column, const QModelIndex & parent) const
// {
//     if (row < 0 || column < 0) return false;

//     return row < rowCount(parent) && column < columnCount(parent);
// }//------------------------------------------------------------------


int TSendParcelTableModel::columnCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return headers.size();
}//------------------------------------------------------------------


int TSendParcelTableModel::rowCount(const QModelIndex & parent) const {
    return _model->getSendStorage().count();
    //return _count_row;
}//------------------------------------------------------------------


QVariant TSendParcelTableModel::data(
    const QModelIndex & index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (role == Qt::DisplayRole) {
        int row = index.row();
        int col = index.column();

        if (row < 0 || row >= rowCount() || col < 0 || col >= columnCount()) {
            return QVariant();
        }

        auto pack = _model->getSendStorage().value(row);

        switch(col){
        case 0:
            return static_cast<int>(pack.type_data);
        case 1:
            return static_cast<int>(pack.type_signal);
        case 2:
            return pack.id;
        case 3:
            return pack.payload.parameter;
        default: return QVariant();
        }
    }

    return QVariant();
}//------------------------------------------------------------------


QVariant TSendParcelTableModel::headerData(
    int section, Qt::Orientation orientation, int role) const
{
    if ((section < 0)
        || ((orientation == Qt::Horizontal) && (section >= columnCount()))
        || ((orientation == Qt::Vertical) && (section >= rowCount())))
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        switch (role) {
        case Qt::DisplayRole:
            return headers[section];
            break;
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}//------------------------------------------------------------------


QModelIndex TSendParcelTableModel::index(
    int row, int column, const QModelIndex & parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}//------------------------------------------------------------------


QModelIndex TSendParcelTableModel::parent(const QModelIndex & index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}//------------------------------------------------------------------


bool TSendParcelTableModel::insertRows(
    int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    //_count_row += count;
    endInsertRows();

    return true;
}//------------------------------------------------------------------


bool TSendParcelTableModel::removeRows(
    int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    //_count_row -= count;
    endRemoveRows();

    return true;
}//------------------------------------------------------------------


void TSendParcelTableModel::addDataRow() {



    // if ( _model->sizeSendStorage() > this->rowCount()) {
    //     beginInsertRows(QModelIndex(), this->rowCount(), _model->sizeSendStorage() - 1 );
    //     _count_row = _model->sizeSendStorage();
    //     endInsertRows();
    // }


    //beginInsertRows();
    //beginMoveRows();
    //beginRemoveRows();
    //beginResetModel();


    // _gridData.push_back(QPair<ViewSendPackage, int>(_model->itemSendStorage(0), 0));
    // _gridData.clear();
    // std::sort(_gridData.begin(), _gridData.end(),
    //     [this](QPair<ViewSendPackage, int>& t1, QPair<ViewSendPackage, int>& t2) {
    //         return t1.first < t2;
    //     }
    // );

    //begin
}//------------------------------------------------------------------


void TSendParcelTableModel::clearTable() {
    beginResetModel();
    //_count_row = 0;
    endResetModel();
}//------------------------------------------------------------------


/* protected: */

void TSendParcelTableModel::headersFormer(){
    headers = {
        "Тип данных", "Тип сигнала", "Номер параметра", "Payload"
    };
}//------------------------------------------------------------------
