#include "nodeparametersdialog.h"
#include "ui_nodeparametersdialog.h"

NodeParametersDialog::NodeParametersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NodeParametersDialog)
{
    ui->setupUi(this);
    ui->tw_node_parameters->verticalHeader()->setHidden(true);
}

NodeParametersDialog::~NodeParametersDialog()
{
    delete ui;
}

QTableWidget * NodeParametersDialog::getTableNodeParameters()
{
    return ui->tw_node_parameters;
}
