#ifndef TTABLEMODEL_H
#define TTABLEMODEL_H

#include <QAbstractTableModel>

class TModelStateInterface;

class TTableModel : public QAbstractTableModel
{
    Q_OBJECT

    TModelStateInterface* _model;

    int _count_row = 0;

public:
    explicit TTableModel(TModelStateInterface* model, QObject *parent = nullptr);
    ~TTableModel();
    
    bool hasIndex(
        int row,
        int column,
        const QModelIndex &parent = QModelIndex()) const;

    virtual int columnCount(
        const QModelIndex& parent = QModelIndex()) const override;

    virtual int rowCount(
        const QModelIndex& parent = QModelIndex()) const override;

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
        const QModelIndex &parent = QModelIndex()) const override;

    virtual QModelIndex parent(
        const QModelIndex &index) const override;

private slots:
    void addDataRow();
    void clearTable();

protected:
    std::vector<QString> headers;
    
    void headersFormer();

}; //class TTableModel
//------------------------------------------------------------

#endif // TTABLEMODEL_H
