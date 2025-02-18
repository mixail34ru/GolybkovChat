#include "TSendParcelTableView.h"

#include <QHeaderView>

TSendParcelTableView::TSendParcelTableView(
    QAbstractTableModel* model, QWidget* parent)
    : QTableView(parent)
{
    this->setModel(model);

    /*verticalHeader*/
    this->verticalHeader()->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);       // автоматический подбор размера до оптимального
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);                  // пользователь не может изменять высоту строки

    /* horizontalHeader */
    this->setSortingEnabled(true);
    this->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter); // автоматическое выравнивание текста
    this->horizontalHeader()->setHighlightSections(true);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);        // пользователь может изменять ширину столбца
    this->horizontalHeader()->setStretchLastSection(true);                           // последний элемент занимает все свободное пространство
}//------------------------------------------------------------------


TSendParcelTableView::~TSendParcelTableView() {
}//------------------------------------------------------------------
