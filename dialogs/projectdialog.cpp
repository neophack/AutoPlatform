#include "projectdialog.h"
#include "ui_projectdialog.h"

#include <QDebug>
#include <QFileDialog>

ProjectDialog::ProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectDialog)
{
    ui->setupUi(this);
    initButton();
    initOpenPath();
}

ProjectDialog::~ProjectDialog()
{
    delete ui;
}

void ProjectDialog::initButton()
{
    int nCount = ui->sw_project->count();
    connect(ui->pb_project_back,&QPushButton::clicked,this,[&,nCount]()
    {
        int nIndex = ui->sw_project->currentIndex();
        if(nIndex>0)
        {
            nIndex--;
            ui->pb_project_back->setEnabled(true);
            ui->pb_project_next->setEnabled(true);
            if(nIndex==0) ui->pb_project_back->setEnabled(false);
        }
        ui->sw_project->setCurrentIndex(nIndex);
    });

    connect(ui->pb_project_next,&QPushButton::clicked,this,[&,nCount]()
    {
        int nIndex = ui->sw_project->currentIndex();
        if(nIndex<nCount)
        {
            nIndex++;
            ui->pb_project_back->setEnabled(true);
            ui->pb_project_next->setEnabled(true);
            if(nIndex==nCount-1) ui->pb_project_next->setEnabled(false);
        }
        ui->sw_project->setCurrentIndex(nIndex);
    });

    connect(ui->pb_project_cancel,&QPushButton::clicked,this,[&]()
    {
         this->close();
    });
}

void ProjectDialog::initOpenPath()
{
    connect(ui->pb_project_path,&QPushButton::clicked,this,[&]()
    {
        QString path = QFileDialog::getExistingDirectory(this,"Choose Directory","./");
        if(path.isEmpty()) return;
        else ui->le_project_path->setText(path);
    });


}
