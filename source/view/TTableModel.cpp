#include "TTableModel.h"
#include "TModelStateInterface.h"

TTableModel::TTableModel(TModelStateInterface* model, QObject *parent)
    : QAbstractTableModel(parent), _model(model)
{
<<<<<<< HEAD
    connect(_model, &TModelStateInterface::recvStorageChanged,
            this, &TTableModel::addDataRow);

    connect(_model, &TModelStateInterface::recvStorageCleared,
            this, &TTableModel::clearTable);
=======
    connect(_model, SIGNAL(storageDataChanged()),
            this, SLOT(addDataRow()));

    connect(_model, SIGNAL(storageClear()),
            this, SLOT(clearTable()));
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884

   headersFormer();
}//------------------------------------------------------------------


TTableModel::~TTableModel() {
}//------------------------------------------------------------------


bool TTableModel::hasIndex(
    int row, int column, const QModelIndex & parent) const
{
    if (row < 0 || column < 0) return false;

    return row < rowCount(parent) && column < columnCount(parent);
}//------------------------------------------------------------------


<<<<<<< HEAD
int TTableModel::columnCount(const QModelIndex & parent) const {
=======
int TTableModel::columnCount(const QModelIndex & parent) const
{
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    Q_UNUSED(parent);
    return headers.size();
}//------------------------------------------------------------------


<<<<<<< HEAD
int TTableModel::rowCount(const QModelIndex & parent) const {
    return _count_row;
}//------------------------------------------------------------------


QString timestampString(std::chrono::high_resolution_clock::time_point timestamp) {
    using namespace std::chrono;
    using days = duration<long long, std::ratio<86400>>;

    const int local_timeshift = 3;

    auto duration = timestamp.time_since_epoch();

    int h = duration_cast<hours>(duration - duration_cast<days>(duration)).count() + local_timeshift;
    int m = duration_cast<minutes>(duration - duration_cast<hours>(duration)).count();
    int s = duration_cast<seconds>(duration - duration_cast<minutes>(duration)).count();
    int ms = duration_cast<milliseconds>(duration - duration_cast<seconds>(duration)).count();

    return QString::number(h) + ":" + QString::number(m) + ":" + QString::number(s) + "." + QString::number(ms);
}//------------------------------------------------------------------


QVariant TTableModel::data(const QModelIndex & index, int role) const {
=======
int TTableModel::rowCount(const QModelIndex & parent) const
{
    return _model->storageSize();
}//------------------------------------------------------------------


QVariant TTableModel::data(const QModelIndex & index, int role) const
{
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    if (!index.isValid()) return QVariant();

    if (role == Qt::DisplayRole)
    {
        int row = index.row();
        int col = index.column();

        if (row < 0 || row >= rowCount() || col < 0 || col >= columnCount())
        {
            return QVariant();
        }

<<<<<<< HEAD

            switch(col){
            case 0:
                return timestampString(_model->timeItem(row).timestamp);
            case 1:
                return _model->storageItem(row).type_data;
            case 2:
                return _model->storageItem(row).type_signal;
            case 3:
                return _model->storageItem(row).id;
            case 4:
                return _model->storageItem(row).payload.parameter;
            default: return QVariant();
            }

=======
        switch(col){
        case 0: return _model->storageItem(row).type_data;
        case 1: return _model->storageItem(row).type_signal;
        case 2: return _model->storageItem(row).id;
        case 3: return _model->storageItem(row).payload.parameter;
        default: return QVariant();
        }
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    }

    return QVariant();
}//------------------------------------------------------------------


QVariant TTableModel::headerData(
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


QModelIndex TTableModel::index(
    int row, int column, const QModelIndex & parent) const
{
    return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
}//------------------------------------------------------------------


QModelIndex TTableModel::parent(const QModelIndex & index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}//------------------------------------------------------------------


void TTableModel::addDataRow() {
<<<<<<< HEAD
    if ( _model->storageSize() > this->rowCount())
    {
        beginInsertRows(QModelIndex(), this->rowCount(), _model->storageSize() - 1 );
        _count_row = _model->storageSize();
        endInsertRows();
    }
=======
    beginInsertRows(QModelIndex(), 0, 0);
    endInsertRows();
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
}//------------------------------------------------------------------


void TTableModel::clearTable() {
    beginResetModel();
<<<<<<< HEAD
    _count_row = 0;
=======
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    endResetModel();
}//------------------------------------------------------------------

/* protected: */

void TTableModel::headersFormer(){
    headers = {
<<<<<<< HEAD
        "Время получения", "Тип данных", "Тип сигнала", "Номер параметра", "Payload"
=======
        "Тип данных", "Тип сигнала", "Номер параметра", "Payload"
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
    };
}//------------------------------------------------------------------
