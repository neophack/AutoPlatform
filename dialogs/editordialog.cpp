#include "editordialog.h"
#include "ui_editordialog.h"
//#include

EditorDialog::EditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditorDialog)
{
    ui->setupUi(this);
}

EditorDialog::~EditorDialog()
{
    delete ui;
}
