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

//std::shared_ptr<DataModelRegistry> MainWindow::registerDataModels()
//{
//    auto ret = std::make_shared<DataModelRegistry>();

//    const QString path = "/home/fc/works/QtProjects/AutoPlatform/AutoPlateform/nodeconfig/";
//    QStringList files = getFlieList(path);

//    moduleLibrary->importFiles(files);
//    std::vector<Invocable> invocableList = moduleLibrary->getInvocableList();

//    for(long int unsigned i=0;i<invocableList.size();i++){
//        const auto &inv = invocableList[i];
//        auto f = [inv](){return std::make_unique<InvocableDataModel>(inv);};
//        //        ret->registerModel<MyDataModel>(f,QString::fromStdString(inv.getName()));

//        //math.hpp的内容注册为MathOperations分类的内容
//        ret->registerModel<MyDataModel>(f,"MathOperations");
//        QSet<QString> category;
//        category = nodeMap.value("MathOperations");
//        category.insert(QString::fromStdString(inv.getName()));
//        nodeMap.insert("MathOperations",category);
//    }

//    nodeTreeDialog->setNodeMap(nodeMap);

//    return ret;
//}

/////初始化主FlowScene
//void MainWindow::initNodeEditor()
//{
//    AICCFlowView *view = this->makeNewNodeEditorScene();

//    QStackedWidget *sw_flowscene =  ui->sw_flowscene;
//    QStackedLayout *layout = new QStackedLayout();
//    layout->addWidget(view);
//    layout->setContentsMargins(0,0,0,0);
//    layout->setSpacing(0);

//    sw_flowscene->widget(0)->setLayout(layout);
//}

/////创建一个新的NodeScene
//AICCFlowView *MainWindow::makeNewNodeEditorScene(){
//    //设置nodeeditor的scene与view
//    auto scene = new FlowScene (this->registerDataModels());
//    auto view = new AICCFlowView(scene);
//    _flowScene = scene;
//    _aiccFlowView = view;

//    view->setAcceptDrops(true);
//    view->setDragMode(QGraphicsView::DragMode::NoDrag);
//    //获得节点属性connect
//    connect(view,&AICCFlowView::getNodeDataModel,this,[&](NodeDataModel *nodeDataModel)
//    {
//        QTableWidget * tw = ui->tableWidget;
//        fillTableData(tw,nodeDataModel);
//    });

//    //双击节点显示节点的属性窗口
//    connect(view,&AICCFlowView::nodeDoubleClicked,this,[&](Node &n)
//    {
//        //临时判断条件，以后需要用其他方式来判断
//        if(n.nodeDataModel()->name()=="subsystem::SubSystem"){
//            return;
//        }

//        npDialog->show();
//        QTableWidget *nptw =  npDialog->getTableNodeParameters();
//        fillTableData(nptw,n.nodeDataModel());
//    });

//    //获得点击libarary browser中按钮的事件
//    connect(nodeTreeDialog,&NodeTreeDialog::nodeDoubleClicked,this,[&](QString name){
//        //此处可在view中创建node
//        _aiccFlowView->createNode(name,QPoint(_flowScene->width()/2,_flowScene->height()/2));

//        qDebug() << "node tree dialog clicked:" << name << endl;
//    });

//    return view;
//}

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

    connect(ui->pb_library_browser,&QPushButton::clicked,this,[&]
    {
        nodeTreeDialog->show();
    });
}

void MainWindow::initBreadcrumbNavigation(){
    QStringList lpath;
    lpath << "root";
    ui->l_breadcrumb_navigation->makeNavigationData(lpath);
    ui->l_breadcrumb_navigation->refreshNavigationView();

    //相应点击链接的操作
    connect(ui->l_breadcrumb_navigation,&AICCBreadcrumbNavigation::linkActivated,this,[&](const QString &link){
//        ui->sw_flowscene->setCurrentIndex()
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
    ui->sw_flowscene->addNewPageFlowScene("root");

}


