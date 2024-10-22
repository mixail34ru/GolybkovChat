#include "TReceiverWidget.h"

#include <QAbstractTableModel>
#include <QTableView>

#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>

#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

TReceiverWidget::TReceiverWidget(QWidget* parent)
    : QWidget(parent)
{
    /* backend */

    //QAbstractTableModel* table_model = new QAbstractTableModel(this);

    /* frontend */

    QGridLayout* grd_lt = new QGridLayout();

    /* Port */

    QHBoxLayout* port_hlt = new QHBoxLayout();

    QLabel* port_lbl = new QLabel(tr("Port:"));
    port_hlt->addWidget(port_lbl);

    QLineEdit* port_txtdt = new QLineEdit(tr("666"));
    port_hlt->addWidget(port_txtdt);

    QPushButton* listen_btn = new QPushButton(tr("Запустить прослушку"));
    port_hlt->addWidget(listen_btn);

    grd_lt->addLayout(port_hlt, 0, 0);

    /* Table */

    QTableView* table = new QTableView();

    QBoxLayout* layout = new QBoxLayout(QBoxLayout::Direction());
    layout->addWidget(table);

    grd_lt->addLayout(layout, 1, 0);

    this->setLayout(grd_lt);
}

TReceiverWidget::~TReceiverWidget() {}
