#include "nodeparametersdialog.h"
#include "ui_nodeparametersdialog.h"

NodeParametersDialog::NodeParametersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NodeParametersDialog)
{
    ui->setupUi(this);
    ui->tw_node_parameters->verticalHeader()->setHidden(true);

    //设置第一列为只读
    ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate(this);
    ui->tw_node_parameters->setItemDelegateForColumn(0,readOnlyDelegate);
}

NodeParametersDialog::~NodeParametersDialog()
{
    delete ui;
}

QTableWidget * NodeParametersDialog::getTableNodeParameters()
{
    return ui->tw_node_parameters;
}
