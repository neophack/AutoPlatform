#include "nodetreedialog.h"
#include "ui_nodetreedialog.h"

NodeTreeDialog::NodeTreeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NodeTreeDialog)
{
    //    moduleLibrary = new ModuleLibrary();
    ui->setupUi(this);

    this->initTreeWidget();
    this->initNodeConfig();
}

NodeTreeDialog::~NodeTreeDialog()
{
    delete ui;
    //    delete moduleLibrary;
}
///初始化属性结构内容
void NodeTreeDialog::initTreeWidget()
{
    AICCTreeWidget *tw = ui->tw_node;
    tw->clear();

    //数学计算部分
    makeRootGroupItem(tw,"MathOperations","Math Operations");
    //驱动部分
    makeRootGroupItem(tw,"Drivers","Drivers");
    //控制算法部分
    makeRootGroupItem(tw,"ControlAlgorithm","Control Algorithm");
    //逻辑运算部分
    makeRootGroupItem(tw,"LogicalOperations","Logical Operations");
    //信号解析
    makeRootGroupItem(tw,"SinalAnalysis","Sinal Analysis");

    connect(ui->tw_node,&AICCTreeWidget::itemClicked,this,&NodeTreeDialog::treeWidgetItemClicked);

    tw->expandAll();
}

///创建属性结构的根目录分类
void NodeTreeDialog::makeRootGroupItem(AICCTreeWidget *atw,const QString name,const QString text)
{
    QTreeWidgetItem *rootGroupMathOperations = new QTreeWidgetItem(atw);
    rootGroupMathOperations->setText(0,text);
    rootGroupMathOperations->setData(0,Qt::UserRole+1,QVariant::fromValue(name));
}

///加载node的数据
void NodeTreeDialog::initNodeConfig()
{}

///获得DataModelRegistry对象
void NodeTreeDialog::setNodeMap(QMap<QString,QSet<QString>> pnm){
    qDebug() << "setNodeMap: " << pnm.size() << "  QSet size: " << pnm["MathOperations"].size();
    _nodeMap = pnm;
}

///根据名称创建button
AICCToolButton * createToolButton( QString name){

    AICCToolButton *tb = new AICCToolButton();
    tb->setText(name);
    tb->setNodeName(name);
    tb->setNodeCaption(name);
    tb->setMinimumSize(100,100);
    QSizePolicy sp = tb->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    tb->setSizePolicy(sp);
    return tb;
}

///点击树形节点后右侧按钮区域变化
void NodeTreeDialog::treeWidgetItemClicked(QTreeWidgetItem *item, int column){
    QList<AICCToolButton*> tbs = ui->gl_node->findChildren<AICCToolButton*>();
    foreach(AICCToolButton *tb,tbs){
        delete tb;
    }

    if(item->data(0,Qt::UserRole+1).value<QString>()==QString::fromStdString("MathOperations")){
        if(_nodeMap.contains("MathOperations"))
        {
            QSet<QString> nodes = _nodeMap["MathOperations"];
            int i = 0;
            foreach( QString name,nodes){
                AICCToolButton *tb = createToolButton(name);

                //点击按钮通知事件
                connect(tb,&QToolButton::clicked,this,[tb,this](bool checked = false){
                    qDebug() << "clicked";
                    emit nodeDoubleClicked(tb->text());
                });

                ui->gl_node->addWidget(tb,i/4,i%4,Qt::AlignHCenter);
                i++;
//                qDebug() << "MathOperations" << _nodeMap["MathOperations"].toList().size() << endl;
            }
        }
    }
}























