#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    projectDialog = new ProjectDialog(parent);
    npDialog = new NodeParametersDialog(parent);
    nodeTreeDialog = new NodeTreeDialog(parent);
    moduleLibrary = new ModuleLibrary();
    ui->setupUi(this);

    this->initMenu();
    this->initTreeView();
    this->setAcceptDrops(true);
    this->initSplitter();
    this->initTableWidget();
    this->initToolbar();
    this->initBreadcrumbNavigation();
    this->initStackedWidget();


    //面包屑导航调试代码,同时显示文本与本地图片资源
    //    img{width:20px;height:20px}
    //    QString str_navigation = QString("<style>a{text-decoration:none;font-size:15px;vertical-align:middle} img{vertical-align:bottom}</style><img src=':/res/breadcrumbNavigation/model_16.png'/><a href='level1' >level1</a><img src=':/res/breadcrumbNavigation/rightArrow_16.png'  />&nbsp;&nbsp;<img src=':/res/breadcrumbNavigation/subsystem_16.png'/><a href='level2'>level2</a><img src=':/res/breadcrumbNavigation/rightArrow_16.png'/>&nbsp;");
    //    ui->l_breadcrumb_navigation->setText(str_navigation);

}

MainWindow::~MainWindow()
{
    delete projectDialog;
    delete npDialog;
    delete nodeTreeDialog;
    delete ui;
    delete moduleLibrary;
    //    delete _flowScene;
    //    delete _aiccFlowView;
}

void MainWindow::initMenu()
{
    connect(ui->actionExit,&QAction::triggered,this,&QWidget::close);
    connect(ui->actionNodeWindow,&QAction::toggled,ui->dw_left,&QDockWidget::setVisible);
    connect(ui->actionPropertyWindow,&QAction::toggled,ui->dw_right,&QDockWidget::setVisible);
    connect(ui->actionAbout,&QAction::triggered,this,&QApplication::aboutQt);
    connect(ui->actionNewProject,&QAction::triggered,projectDialog,&ProjectDialog::show);
}

void MainWindow::setTreeNode(QTreeWidget *tw,const char* ptext,const char* picon){
    QTreeWidgetItem *pItem = new QTreeWidgetItem();
    pItem->setText(0,ptext);
    QIcon icon;
    icon.addPixmap(QPixmap(picon));
    pItem->setIcon(0,icon);

    tw->addTopLevelItem(pItem);
}

void MainWindow::initTreeView()
{
    AICCTreeWidget *tw = ui->tw_node;
    tw->setDragDropMode(QAbstractItemView::DragOnly);
    tw->setDragEnabled(true);
    tw->clear();

    QTreeWidgetItem* rootGroupSource = new QTreeWidgetItem(tw);
    rootGroupSource->setText(0,QStringLiteral("数据源"));
    QTreeWidgetItem* itemSource1 = new QTreeWidgetItem(rootGroupSource);
    itemSource1->setText(0,QStringLiteral("设备"));
    QTreeWidgetItem* itemSource2 = new QTreeWidgetItem(rootGroupSource);
    itemSource2->setText(0, QStringLiteral("ECU"));
    QTreeWidgetItem* itemSourceCalculator = new QTreeWidgetItem(rootGroupSource);
    itemSourceCalculator->setText(0, QStringLiteral("四则运算源数据"));
    itemSourceCalculator->setData(0,Qt::UserRole+1, QStringLiteral("AICCNumberSource"));


    QTreeWidgetItem* rootGroupProcess = new QTreeWidgetItem(tw);
    rootGroupProcess->setText(0,QStringLiteral("过程"));
    QTreeWidgetItem* itemProcess1 = new QTreeWidgetItem(rootGroupProcess);
    itemProcess1->setText(0, QStringLiteral("驱动"));

    QTreeWidgetItem* itemProcess2 = new QTreeWidgetItem(rootGroupProcess);
    itemProcess2->setText(0, QStringLiteral("算法"));
    QTreeWidgetItem* itemProcessCalculatorAddition = new QTreeWidgetItem(itemProcess2);
    itemProcessCalculatorAddition->setText(0, QStringLiteral("加法"));
    itemProcessCalculatorAddition->setData(0,Qt::UserRole+1, QStringLiteral("AICCAdditionOperation"));
    QTreeWidgetItem* itemProcessCalculatorSubstraction = new QTreeWidgetItem(itemProcess2);
    itemProcessCalculatorSubstraction->setText(0, QStringLiteral("减法"));
    itemProcessCalculatorSubstraction->setData(0,Qt::UserRole+1, QStringLiteral("AICCSubtractionOperation"));
    QTreeWidgetItem* itemProcessCalculatorMultiplication = new QTreeWidgetItem(itemProcess2);
    itemProcessCalculatorMultiplication->setText(0, QStringLiteral("乘法"));
    itemProcessCalculatorMultiplication->setData(0,Qt::UserRole+1, QStringLiteral("AICCMultiplicationOperation"));
    QTreeWidgetItem* itemProcessCaculatorDivision = new QTreeWidgetItem(itemProcess2);
    itemProcessCaculatorDivision->setText(0, QStringLiteral("除法"));
    itemProcessCaculatorDivision->setData(0,Qt::UserRole+1, QStringLiteral("AICCDivisionOperation"));

    QTreeWidgetItem* itemProcess3 = new QTreeWidgetItem(rootGroupProcess);
    itemProcess3->setText(0, QStringLiteral("信号"));
    QTreeWidgetItem* itemProcess4 = new QTreeWidgetItem(rootGroupProcess);
    itemProcess4->setText(0, QStringLiteral("IO"));


    QTreeWidgetItem* rootGroupResult = new QTreeWidgetItem(tw);
    rootGroupResult->setText(0,QStringLiteral("数据目标"));
    QTreeWidgetItem* itemResultCalculator = new QTreeWidgetItem(rootGroupResult);
    itemResultCalculator->setText(0, QStringLiteral("四则运算结果"));
    itemResultCalculator->setData(0,Qt::UserRole+1, QStringLiteral("AICCNumberResult"));

    ui->tw_node->expandAll();
    //    QTreeWidgetItemIterator it(ui->treeWidget);
    //    while(*it)
    //    {
    //        (*it)->setCheckState(0,Qt::Checked);
    //        ++it;
    //    }


    //    setTreeNode(tw,"设备",":/res/ticon1.png");
    //    setTreeNode(tw,"ECU",":/res/ticon1.png");
    //    setTreeNode(tw,"驱动",":/res/ticon1.png");
    //    setTreeNode(tw,"算法",":/res/ticon1.png");
    //    setTreeNode(tw,"信号",":/res/ticon1.png");
    //    setTreeNode(tw,"IO",":/res/ticon1.png");
}

///填充节点属性表格数据
void MainWindow::fillTableData(QTableWidget *tw,const NodeDataModel *ndm)
{
    tw->setRowCount(0);
    if(ndm==Q_NULLPTR) return;
    tw->setRowCount(tw->rowCount()+1);
    tw->setItem(0,0,new QTableWidgetItem("caption"));
    tw->setItem(0,1,new QTableWidgetItem(ndm->caption()));

    tw->setRowCount(tw->rowCount()+1);
    tw->setItem(1,0,new QTableWidgetItem("name"));
    tw->setItem(1,1,new QTableWidgetItem(ndm->name()));

    qDebug() << "emit getNodeDataModel";
}

void MainWindow::initSplitter()
{
    ui->dw_left->hide();
    ui->dw_right->hide();
}

///初始化右侧属性表格
void MainWindow::initTableWidget()
{
    ui->tw_nodeProperties->verticalHeader()->setHidden(true);
}

///初始化工具条
void MainWindow::initToolbar()
{
    //隐藏掉上方dock的标题栏
    QWidget *titleBarWidget = ui->dw_toolbar->titleBarWidget();
    QWidget *nullTitleBarWidget = new QWidget();
    ui->dw_toolbar->setTitleBarWidget(nullTitleBarWidget);
    delete titleBarWidget;

    //初始化tab标签
    ui->tw_toolbar->setTabText(0,"编辑器");
    ui->tw_toolbar->setTabText(1,"编译器");
    ui->tw_toolbar->setTabText(2,"仿真器");
    ui->tw_toolbar->setTabText(3,"在线标定");
    ui->tw_toolbar->setTabText(4,"模块自定义");

    //显示node模块的窗口
    connect(ui->pb_library_browser,&QPushButton::clicked,this,[&]{
        nodeTreeDialog->show();
    });

    //生成代码按钮
    connect(ui->pb_script_generator,&QPushButton::clicked,this,[&]{
        //此处为临时路径,以后需要改进这种方案
         std::ofstream file("/home/fc/works/CLionProjects/runtime/test/generate.cpp");
         if(!file){
             QMessageBox::critical(Q_NULLPTR,"发生错误","打开文件失败");
             return;
         }

         AICCFlowView * fv = static_cast<AICCFlowView *>(ui->sw_flowscene->currentWidget());
         SourceGenerator::generate(*(fv->scene()),file);
    });

    //打开按钮响应动作
    connect(ui->pb_open,&QPushButton::clicked,this,[&]{
        //1：加载配置文件初始化各项数据
        QString fileName = QFileDialog::getOpenFileName(Q_NULLPTR,tr("Open Project"),QDir::homePath(),tr("Project (*.xml)"));
        if(!QFileInfo::exists(fileName)) return;
        QFile file(fileName);
        projectDialog->readProjectXml(file);

        //2：将名称为mainFlowScene的文件内容加载到主FlowScene上
        QString loadFileName = projectDialog->getProjectPath()+"/"+projectDialog->getProjectName()+"/"+ projectDialog->getFlowSceneSaveFiles()[0];
        if (!QFileInfo::exists(loadFileName)) return;

        QFile loadFile(loadFileName);
        if(!loadFile.open(QIODevice::ReadOnly)) return;

        FlowScene *scene =  static_cast<AICCFlowView *>(ui->sw_flowscene->currentWidget())->scene();
        scene->clearScene();
        QByteArray wholeFile = loadFile.readAll();
        scene->loadFromMemory(wholeFile);
    });

    //保存按钮响应动作，当前只保存一个NodeEditor的内容，子系统实现后需要保存多个NodeEditor内容
    connect(ui->pb_save,&QPushButton::clicked,this,[&]{
        //0：判断当前是否为未关联项目，如未关联项目要求用户先创建项目
        if(projectDialog->getProjectName()==""){
            int result  = projectDialog->exec();
            if(result==QDialog::Rejected) return;
        }

        //1：加载项目文件，初始化所有项目数据
//        QString fileName = QFileDialog::getOpenFileName(Q_NULLPTR,tr("Open Project"),QDir::homePath(),tr("Project (*.xml)"));
        QString fileName = projectDialog->getProjectPath()+"/"+projectDialog->getProjectName()+"/.ap/project.xml";
        if(!QFileInfo::exists(fileName)) return;
        QFile file(fileName);
        projectDialog->readProjectXml(file);

        //2：保存当前内容到flow文件中
         AICCFlowView *fv = static_cast<AICCFlowView *>(ui->sw_flowscene->currentWidget());
         qDebug() << projectDialog->getProjectPath()<< "   "<< projectDialog->getProjectName();
         if(projectDialog->getProjectPath()=="" || projectDialog->getProjectName()==""){
             QMessageBox::critical(Q_NULLPTR,"critical","请先选择项目再进行保存",QMessageBox::Ok,QMessageBox::Ok);
             return;
         }

         for(QString ssf :projectDialog->getFlowSceneSaveFiles()){
            QString saveFileName = projectDialog->getProjectPath()+"/"+projectDialog->getProjectName()+"/"+ssf;
            qDebug() << "save file name:" << saveFileName;
            QFile file(saveFileName);
            if(file.open(QIODevice::WriteOnly)){
                file.write(fv->scene()->saveToMemory());
            }
         }
    });
}

void MainWindow::initBreadcrumbNavigation(){
    QStringList lpath;
    lpath << "root";
    ui->l_breadcrumb_navigation->makeNavigationData(lpath);
    ui->l_breadcrumb_navigation->refreshNavigationView();

    //相应点击链接的操作
    connect(ui->l_breadcrumb_navigation,&AICCBreadcrumbNavigation::linkActivated,this,[&](const QString &link){
        ui->sw_flowscene->setCurrPagePathName(link);
        qDebug() << "clicked link:" << link ;
    });
}

///初始化StackedWidget
void MainWindow::initStackedWidget(){

    ///nodeeditor数据注册完后，要将数据传递给NodeTreeDialog窗口使用
    connect(ui->sw_flowscene,&AICCStackedWidget::registerDataModelsCompleted,this,[&](const QMap<QString,QSet<QString>> nodeMap){
        nodeTreeDialog->setNodeMap(nodeMap);
    });

    ///获得数据后填充右侧属性窗口
    connect(ui->sw_flowscene,&AICCStackedWidget::getNodeDataModel,this,[&](NodeDataModel *ndm){
        QTableWidget *tw = ui->tw_nodeProperties;
        tw->setRowCount(0);
        if(ndm==Q_NULLPTR) return;
        tw->setRowCount(tw->rowCount()+1);
        tw->setItem(0,0,new QTableWidgetItem("caption"));
        tw->setItem(0,1,new QTableWidgetItem(ndm->caption()));

        tw->setRowCount(tw->rowCount()+1);
        tw->setItem(1,0,new QTableWidgetItem("name"));
        tw->setItem(1,1,new QTableWidgetItem(ndm->name()));
    });

    ///双击node节点模块后弹出显示属性的窗口
    connect(ui->sw_flowscene,&AICCStackedWidget::nodeDoubleClicked,this,[&](NodeDataModel *nodeDataModel,const QString &pagePathName){
        //如果点击的是子窗口模块不进行处理
        if(nodeDataModel->name()=="subsystem::SubSystem"){
            return;
        }

        npDialog->show();
        QTableWidget *nptw =  npDialog->getTableNodeParameters();
        fillTableData(nptw,nodeDataModel);
    });

    ///通知当前页面改变
    connect(ui->sw_flowscene,&AICCStackedWidget::notifyCurrentPagePathNameChanged,ui->sw_flowscene,[&](const QString &url){
        ui->sw_flowscene->setCurrentUrl(url);
    });
    ///通知面包屑导航改变
    connect(ui->sw_flowscene,&AICCStackedWidget::notifyCurrentPagePathNameChanged,ui->l_breadcrumb_navigation,[&](const QString &url){
        ui->l_breadcrumb_navigation->makeNavigationData(url);
        ui->l_breadcrumb_navigation->refreshNavigationView();
    });

    ///向StackedWidget控件中增加第一个页面，并增加第一个FlowScene
    ui->sw_flowscene->addNewPageFlowScene("");

}


