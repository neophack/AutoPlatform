#include "projectdialog.h"
#include "ui_projectdialog.h"

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

///初始化所有按钮
void ProjectDialog::initButton()
{
    ui->pb_project_finish->hide();
    int nCount = ui->sw_project->count();

    //back button event
    connect(ui->pb_project_back,&QPushButton::clicked,this,[&]()
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
    connect(ui->pb_project_finish,&QPushButton::clicked,this,[&,this]()
    {
        //create folder
        QDir folder;
        //        QString fullpath = projectPath+"/"+projectName+"/.ap";

        //创建项目文件夹
        QString projectFolder = projectPath+"/"+projectName;
        QString projectConfigFolder = projectFolder+"/.ap";

        bool existProjectFolder = folder.exists(projectFolder);
        if(existProjectFolder)
        {
            QMessageBox::information(this,tr("create folder"),tr("the folder is existed,please select other path"));
            return;
        }
        else
        {
            bool pfok = folder.mkdir(projectFolder);
            if(!pfok)
            {
                QMessageBox::information(this,tr("create folder"),tr("create folder failed:").append(projectFolder));
                return;
            }
            //创建配置信息文件夹

            bool pcfok = folder.mkdir(projectConfigFolder);
            if(!pcfok)
            {
                QMessageBox::information(this,tr("create .ap folder"),tr("create .ap folder failed:").append(projectConfigFolder));
                return;
            }
        }


        //create project file
        QFile file(projectConfigFolder+"/project.xml");
        bool file_exist = file.exists();
        if(!file_exist)
        {
            if(file.open(QFile::ReadWrite))
            {
                writeProjectXml(file);

                this->accept();
            }
        }
    });


    //项目StackedWidget切换事件
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

///写入项目配置xml文件
void ProjectDialog::writeProjectXml(QFile &file)
{
    QDomDocument doc;
    //写入头数据
    QDomProcessingInstruction instruction;
    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    //根节点，记录项目名称
    QDomElement root = doc.createElement("Project");
    root.setAttribute("name",projectName);
    doc.appendChild(root);

    //FlowScene容器，可记录多个FlowScene,默认创建1个FlowScene
    QDomElement flowScenes = doc.createElement("FlowScenes");
    root.appendChild(flowScenes);
    QDomElement mainFlowScene = doc.createElement("FlowScene");
    mainFlowScene.setAttribute("name","mainScene");
    mainFlowScene.setAttribute("saveFile","mainScene.flow");
    flowScenes.appendChild(mainFlowScene);

    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}

///读取项目文件，当前只读取project的name值
void ProjectDialog::readProjectXml(QFile &file){
    QDomDocument doc;

    if(!doc.setContent(&file)){
        file.close();
        return;
    }

    //获取项目名称
    QDomElement root = doc.documentElement();
    this->projectName = root.attributeNode("name").value();

    //获取项目路径
    QStringList qsl = file.fileName().split("/"+this->projectName+"/.ap");
    this->setProjectPath(qsl[0]);

    if(this->projectName==""){
        QMessageBox::critical(Q_NULLPTR,"critical","项目文件出错，请重新选择项目文件",QMessageBox::Ok,QMessageBox::Ok);
        return;
    }

    QDomNodeList flowScenes = root.childNodes().item(0).childNodes();
    for(int i=0;i<flowScenes.count();i++){
        QDomNode flowScene = flowScenes.item(i);
        flowSceneSaveFiles.append(flowScene.toElement().attributeNode("saveFile").value());
    }

}

const QString &ProjectDialog::getProjectPath() const
{
    return projectPath;
}

const QString &ProjectDialog::getProjectName() const
{
    return projectName;
}

const QStringList &ProjectDialog::getFlowSceneSaveFiles() const
{
    return flowSceneSaveFiles;
}

void ProjectDialog::setProjectPath(const QString &newProjectPath)
{
    projectPath = newProjectPath;
}
