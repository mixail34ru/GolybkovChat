#include "../../include/view/TTableView.h"

#include <QHeaderView>

TTableView::TTableView(QAbstractTableModel* model, QWidget* parent)
<<<<<<< HEAD
    : QTableView(parent)
=======
    :QTableView(parent)
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
{
    this->setModel(model);

    /*verticalHeader*/
    this->verticalHeader()->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);       // автоматический подбор размера до оптимального
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);                  // пользователь не может изменять высоту строки

    /* horizontalHeader */
    this->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter); // автоматическое выравнивание текста
    this->horizontalHeader()->setHighlightSections(true);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);        // пользователь может изменять ширину столбца
    this->horizontalHeader()->setStretchLastSection(true);                           // последний элемент занимает все свободное пространство
<<<<<<< HEAD
}//------------------------------------------------------------------


TTableView::~TTableView() {
}//------------------------------------------------------------------
=======
}

TTableView::~TTableView()
{
}
>>>>>>> 43864b7da22d6974d3306a3a1e5ea6875b8c1884
