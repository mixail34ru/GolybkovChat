#include "TReceiverWidget.h"

#include "TModelStateInterface.h"
#include "TRecvModeGroupBox.h"

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

#include "TTableModel.h"
#include "TTableView.h"


TReceiverWidget::TReceiverWidget(TModelStateInterface* model, QWidget* parent)
    : QWidget(parent)
{
    QGridLayout* grd_lt = new QGridLayout();

    _mode_grp_bx = new TRecvModeGroupBox(model, this);
    connect(
        _mode_grp_bx, &TRecvModeGroupBox::receivePackageActivated,
        this, &TReceiverWidget::receivePackageActivated
    );
    connect(
        _mode_grp_bx, &TRecvModeGroupBox::clearReceiveStorageActivated,
        this, &TReceiverWidget::clearReceiveStorageActivated
    );

    TTableModel* table_model = new TTableModel(model, this);
    TTableView* table = new TTableView(table_model, this);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(_mode_grp_bx);
    layout->addWidget(table);

    grd_lt->addLayout(layout, 1, 0);

    this->setLayout(grd_lt);
}//------------------------------------------------------------------


TReceiverWidget::~TReceiverWidget() {
}//------------------------------------------------------------------
