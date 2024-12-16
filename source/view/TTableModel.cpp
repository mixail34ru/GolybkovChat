#include "TTableModel.h"
#include "TModelStateInterface.h"

TTableModel::TTableModel(TModelStateInterface* model, QObject *parent)
    : QAbstractTableModel(parent), _model(model)
{
    connect(_model, SIGNAL(storageDataChanged()),
            this, SLOT(addDataRow()));

    connect(_model, SIGNAL(storageClear()),
            this, SLOT(clearTable()));

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


int TTableModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return headers.size();
}//------------------------------------------------------------------


int TTableModel::rowCount(const QModelIndex & parent) const
{
    return _count_row;
    //int i = _model->storageSize();
    //return _model->storageSize();
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
    if (!index.isValid()) return QVariant();

    if (role == Qt::DisplayRole)
    {
        int row = index.row();
        int col = index.column();

        if (row < 0 || row >= rowCount() || col < 0 || col >= columnCount())
        {
            return QVariant();
        }


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
    if ( _model->storageSize() > this->rowCount())
    {
        beginInsertRows(QModelIndex(), this->rowCount(), _model->storageSize() - 1 );
        _count_row = _model->storageSize();
        endInsertRows();
    }
}//------------------------------------------------------------------


void TTableModel::clearTable() {
    beginResetModel();
    _count_row = 0;
    endResetModel();
}//------------------------------------------------------------------

/* protected: */

void TTableModel::headersFormer(){
    headers = {
        "Время получения", "Тип данных", "Тип сигнала", "Номер параметра", "Payload"
    };
}//------------------------------------------------------------------
