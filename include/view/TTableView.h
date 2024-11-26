#ifndef TTABLEVIEW_H
#define TTABLEVIEW_H

#include <QTableView>

class TTableView : public QTableView
{
    Q_OBJECT
public:
    explicit TTableView(QAbstractTableModel* model, QWidget* parent);
    ~TTableView();

}; //class TTableView
//-------------------------------------------------------------------

#endif // TTABLEVIEW_H
