#include "projectdialog.h"
#include "ui_projectdialog.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QtXml/QDomDocument>

ProjectDialog::ProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectDialog)
{
    ui->setupUi(this);
    initButton();
    initOpenPath();
    initStackedFirst();
    initStackedSecond();
}

ProjectDialog::~ProjectDialog()
{
    delete ui;
}

void ProjectDialog::initButton()
{
    ui->pb_project_finish->hide();
    int nCount = ui->sw_project->count();

    //back button event
    connect(ui->pb_project_back,&QPushButton::clicked,this,[&,nCount]()
    {
        int nIndex = ui->sw_project->currentIndex();
        if(nIndex>0)
        {
            nIndex--;
            if(nIndex==0) ui->pb_project_back->setEnabled(false);
        }
        ui->sw_project->setCurrentIndex(nIndex);
    });

    //next button event
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

    //cancel button event
    connect(ui->pb_project_cancel,&QPushButton::clicked,this,[&]()
    {
        this->close();
    });


    //finish button event
    connect(ui->pb_project_finish,&QPushButton::clicked,this,[&]()
    {


        //create folder
        QDir folder;
        bool exist = folder.exists(projectPath+"/.ap");
        if(exist)
        {
            QMessageBox::information(this,tr("create folder"),tr("the folder is existed,please select other path"));
            return;
        }
        else
        {
            bool ok = folder.mkdir(projectPath+"/.ap");
            if(!ok)
            {
                QMessageBox::information(this,tr("create folder"),tr("create folder failed:").append(projectPath+"/.ap"));
                return;
            }
        }

        //create project file
        QFile file(projectPath+"/.ap"+"/project.xml");
        bool file_exist = file.exists();
        if(!exist)
        {
            if(file.open(QFile::ReadWrite))
            {
                writeProjectXml();

            }

        }
        else
        {

        }


    });


    //StackedWidget change event
    connect(ui->sw_project,&QStackedWidget::currentChanged,this,[&](int currentPage)
    {
        switch(currentPage)
        {
        case 0:
            ui->pb_project_back->setEnabled(false);
            ui->pb_project_next->setEnabled(true);
            ui->le_project_name->setFocus();
            break;
        case 1:
            ui->pb_project_back->setEnabled(true);
            ui->pb_project_next->setEnabled(true);
            ui->le_config1->setFocus();
            ui->pb_project_finish->hide();
            break;
        case 2:
            ui->pb_project_back->setEnabled(true);
            ui->pb_project_next->setEnabled(false);
            ui->pb_project_finish->show();
            break;
        default:
            break;
        }
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

void ProjectDialog::initStackedFirst()
{
    connect(ui->le_project_name,&QLineEdit::textChanged,this,[&](const QString &str){projectName = str;ui->le_summary_project_name->setText(projectName);});
    connect(ui->le_project_path,&QLineEdit::textChanged,this,[&](const QString &str){projectPath = str;ui->le_summary_project_path->setText(projectPath);});
}

void ProjectDialog::initStackedSecond()
{
    connect(ui->le_config1,&QLineEdit::textChanged,this,[&](const QString &str){config1 = str;ui->le_summary_config1->setText(config1);});
    connect(ui->le_config2,&QLineEdit::textChanged,this,[&](const QString &str){config2=str;ui->le_summary_config2->setText(config2);});
}

void ProjectDialog::writeProjectXml()
{
    QDomDocument doc;
    //write head data
    QDomProcessingInstruction instruction;
}
