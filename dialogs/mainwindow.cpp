#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    sqlite.initDatabaseConnection();
    //    _moduleLibrary = QSharedPointer<ModuleLibrary>(new ModuleLibrary());
    ui->setupUi(this);
    this->setAttribute(Qt::WA_QuitOnClose);
    projectDialog = new ProjectDialog(this);
    npDialog = new NodeParametersDialog(this);
    isDialog = new ImportScriptDialog(this);
    nodeTreeDialog = new NodeTreeDialog(this);


    this->initMenu();
    this->initTreeView();
    this->setAcceptDrops(true);
    this->initSplitter();
    this->initTableWidget();
    this->initToolbar();
    this->initBreadcrumbNavigation();
    this->initStackedWidget();
    this->initNodeEditor();
    this->initImportScriptDialog();


}

MainWindow::~MainWindow()
{
    sqlite.closeConnection();
    delete projectDialog;
    delete npDialog;
    delete nodeTreeDialog;
    delete isDialog;
    delete ui;

}

void MainWindow::initMenu()
{
    connect(ui->actionExit,&QAction::triggered,this,&QWidget::close);
    connect(ui->actionNodeWindow,&QAction::toggled,ui->dw_left,&QDockWidget::setVisible);
    connect(ui->actionPropertyWindow,&QAction::toggled,ui->dw_right,&QDockWidget::setVisible);
    connect(ui->actionAbout,&QAction::triggered,this,&QApplication::aboutQt);
    connect(ui->actionNewProject,&QAction::triggered,projectDialog,&ProjectDialog::show);
    connect(ui->actionOpen,&QAction::triggered,this,&MainWindow::pbOpenAction);
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

    //导入脚本按钮
    connect(ui->pb_import,&QPushButton::clicked,this,[&]{
        isDialog->show();
    });

    //打开按钮响应动作
    connect(ui->pb_open,&QPushButton::clicked,this,&MainWindow::pbOpenAction);

    //保存按钮响应动作，当前只保存一个NodeEditor的内容，子系统实现后需要保存多个NodeEditor内容
    connect(ui->pb_save,&QPushButton::clicked,this,[&]{
        //0：判断当前是否为未关联项目，如未关联项目要求用户先创建项目
        if(projectDialog->getProjectName()==""){
            int result  = projectDialog->exec();
            if(result==QDialog::Rejected) return;
        }

        //1：加载项目文件，初始化所有项目数据
        //        QString fileName = QFileDialog::getOpenFileName(this,tr("Open Project"),QDir::homePath(),tr("Project (*.xml)"));
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


///动作函数部分
void MainWindow::pbOpenAction(){
    //1：加载配置文件初始化各项数据
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Project"),QDir::homePath(),tr("Project (*.xml)"));
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
}


///NodeEditor数据处理部分
//初始化时初始化主Scene的右键菜单，和NodeTreeDialog的node分类数据
void MainWindow::initNodeEditor(){
    _moduleLibrary = QSharedPointer<ModuleLibrary>(new ModuleLibrary());
    //1:先解析文件，准备好解析文件中的node数据
    const QString path = QApplication::applicationDirPath()+"/nodeconfig/";
    QStringList files = getFlieList(path);

    //0:执行加载前准备动作
    ui->statusbar->showMessage("开始加载Node模块数据...");
    ui->tw_toolbar->setEnabled(false);

    //耗时操作放到单独线程中操作，操作完毕后通知外部继续执行
    QtConcurrent::run([&,files](){
        _moduleLibrary->importFiles(files);
        std::list<Invocable> parserResult = _moduleLibrary->getParseResult();
        emit scriptParserCompleted(parserResult);
    });

    //接收scriptParserCompleted信号，执行后续操作
    //为connect注册std::list<Invocable>类型，否则connect在SLOT中会不识别该类型
    qRegisterMetaType<std::list<Invocable>>("std::list<Invocable>");
    connect(this,&MainWindow::scriptParserCompleted,this,&MainWindow::registrySceneGenerateNodeMenu);
    //显示状态栏进度数据
    connect(_moduleLibrary.get(),&ModuleLibrary::fileParserCompleted,this,[&](const int count ,const int index,const QString filename){
        //加载过程中显示当前进度
        ui->statusbar->showMessage("已加载Node模块:"+filename+"("+QString::number(index+1)+"/"+QString::number(count)+")",(index+1)>=count ? 3000 : 0);
    });
}

void MainWindow::registrySceneGenerateNodeMenu(std::list<Invocable> parserResult){
    //2:生成scene的右键node数据,并注册到所有scene中
    std::shared_ptr<DataModelRegistry> registerDataModels = this->registerDataModels(parserResult);
    std::list<FlowScene *> scenes =  ui->sw_flowscene->allScenes();
    for(FlowScene *scene:scenes){
        scene->setRegistry(registerDataModels);
    }

    //3:生成NodeTreeDialog的node菜单结构
    QMap<QString,QSet<QString>> nodeCategoryDataModels = this->nodeCategoryDataModels(parserResult);
    nodeTreeDialog->setNodeMap(nodeCategoryDataModels);

    //4:启用工具栏
//    ui->tw_toolbar->setTabEnabled(true);
    qDebug() << "tw_toolbar->setEnabled(true)";
    ui->tw_toolbar->setEnabled(true);
    ui->menubar->setEnabled(true);
}

///初始化导入脚本对话框的内容
void MainWindow::initImportScriptDialog(){
    //选择文本后响应函数
    connect(isDialog,&ImportScriptDialog::filesSelected,this,[&](const QStringList files){

        QtConcurrent::run([&,files](){
            //1:解析选择文件中的node
            _moduleLibrary->importFiles(files);
            std::list<Invocable> parserResult = _moduleLibrary->getParseResult();
            //此处只通知initNodeEditor函数中链接的registrySceneGenerateNodeMenu函数执行后续操作即可
            emit scriptParserCompleted(parserResult);
        });
    });

    //文件解析百分比
    connect(_moduleLibrary.get(),&ModuleLibrary::fileParserCompleted,this,[&](const int count,const int index,const QString filename){
        isDialog->setImportProcess(index,count);
        isDialog->setListModels(_moduleLibrary.get());
    });
}


//只负责注册右键菜单，并返回右键菜单的数据模型
std::shared_ptr<DataModelRegistry> MainWindow::registerDataModels(const std::list<Invocable> parserResult){
    auto ret = std::make_shared<DataModelRegistry>();
    AICCSqlite sqlite;
    for(auto it = parserResult.begin();it!=parserResult.end();++it){
        const auto &inv = *it;
        QSqlQuery squery = sqlite.query("select n.name,n.caption,nc.class_name from node n inner join nodeClass nc on n.class_id = nc.id where n.name = '"+QString::fromStdString(inv.getName())+"'");
        if(squery.next()){
            QString caption = squery.value(1).toString();
            QString className = squery.value(2).toString();
            auto f = [inv,caption](){
                std::unique_ptr<InvocableDataModel> p = std::make_unique<InvocableDataModel>(inv);
                p.get()->setCaption(caption);
                return p;
            };
            ret->registerModel<MyDataModel>(f,className);
        }else{
            auto f = [inv](){
                std::unique_ptr<InvocableDataModel> p = std::make_unique<InvocableDataModel>(inv);
                p.get()->setCaption(p.get()->name());
                return p;
            };
            ret->registerModel<MyDataModel>(f,"Other");
        }
    }
    return ret;
}

//只负责NodeTreeDialog的node模块分类
QMap<QString,QSet<QString>> MainWindow::nodeCategoryDataModels(const std::list<Invocable> parserResult){
    QMap<QString,QSet<QString>> ret;
    //定义写入分类数据函数
    auto f_insertNodeCategoryMap = [&ret](const QString className,const QString nodeName){
        QSet<QString> category;
        category = ret.value(className);
        category.insert(nodeName);
        ret.insert(className,category);
    };
    AICCSqlite sqlite;
    for(auto it = parserResult.begin();it!=parserResult.end();++it){
        const auto &inv = *it;
        QSqlQuery squery = sqlite.query("select n.name,n.caption,nc.class_name from node n inner join nodeClass nc on n.class_id = nc.id where n.name = '"+QString::fromStdString(inv.getName())+"'");
        if(squery.next()){
            QString className = squery.value(2).toString();
            f_insertNodeCategoryMap(className,QString::fromStdString(inv.getName()));
        }else{
            f_insertNodeCategoryMap("Other",QString::fromStdString(inv.getName()));
        }
    }
    return ret;
}


