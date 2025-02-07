#ifndef TSENDPARCELTABLEVIEW_H
#define TSENDPARCELTABLEVIEW_H

#include <QTableView>

class TSendParcelTableView : public QTableView
{
    Q_OBJECT
public:
    explicit TSendParcelTableView(
        QAbstractTableModel* model, QWidget* parent = nullptr);
    ~TSendParcelTableView();

};//class TSendParcelTableView
//-------------------------------------------------------------------

#endif // TSENDPARCELTABLEVIEW_H
