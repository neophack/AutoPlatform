#include "importscriptdialog.h"
#include "ui_importscriptdialog.h"

ImportScriptDialog::ImportScriptDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportScriptDialog)
{
    ui->setupUi(this);
    this->initButton();
}

ImportScriptDialog::~ImportScriptDialog()
{
    delete ui;
}

///初始化导入按钮操作
void ImportScriptDialog::initButton(){
    connect(ui->pb_import,&QPushButton::clicked,this,[&](){
        QStringList files = QFileDialog::getOpenFileNames(this,"请选择C++头文件",QString(),"C++头文件(*.hpp)",Q_NULLPTR,QFileDialog::ReadOnly);
        if(!files.isEmpty()){
            emit filesSelected(files);
        }
    });
}

///设置进度条百分比
void ImportScriptDialog::setImportProcess(const int cvalue,const int mvalue){
    ui->progressBar->setRange(0,mvalue);
    ui->progressBar->setValue(cvalue+1);
}

void ImportScriptDialog::setListModels(ModuleLibrary *moduleLibrary){
    ui->list->setModel(moduleLibrary);
}
