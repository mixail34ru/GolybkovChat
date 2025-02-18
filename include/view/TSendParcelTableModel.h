#ifndef TSENDPARCELTABLEMODEL_H
#define TSENDPARCELTABLEMODEL_H

//#include <TPackageFormat.h>

#include <QAbstractTableModel>

//#include <QPair>
//#include <QVector>


class TModelStateInterface;

class TSendParcelTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TSendParcelTableModel(
        TModelStateInterface* model, QObject* parent = nullptr);
    virtual ~TSendParcelTableModel();

    // bool hasIndex(
    //     int row,
    //     int column,
    //     const QModelIndex &parent = QModelIndex()) const;

    virtual int columnCount(
        const QModelIndex& parent = QModelIndex()
        ) const override;

    virtual int rowCount(
        const QModelIndex& parent = QModelIndex()
        ) const override;

    virtual QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole
        ) const override;

    virtual QVariant headerData(
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole
        ) const override;

    virtual QModelIndex index(
        int row,
        int column,
        const QModelIndex &parent = QModelIndex()
        ) const override;

    virtual QModelIndex parent(
        const QModelIndex &index
        ) const override;

    virtual bool insertRows(
        int row,
        int count,
        const QModelIndex &parent = QModelIndex()
        ) override;

    virtual bool removeRows(
        int row,
        int count,
        const QModelIndex &parent = QModelIndex()
        ) override;

protected:
    std::vector<QString> headers;

    void headersFormer();

private:
    TModelStateInterface* _model;

    // пара <копия значения, индекс исходника>
    //QVector<QPair<ViewSendPackage, int>> _gridData;

    int _count_row;

private slots:
    void addDataRow();
    void clearTable();

}; //class TSendParcelTableModel
//-------------------------------------------------------------------

#endif // TSENDPARCELTABLEMODEL_H
