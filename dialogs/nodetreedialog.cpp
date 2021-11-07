#include "nodetreedialog.h"
#include "ui_nodetreedialog.h"

NodeTreeDialog::NodeTreeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NodeTreeDialog)
{
    ui->setupUi(this);

    this->initTreeWidget();
    this->initToolBar();
}

NodeTreeDialog::~NodeTreeDialog()
{
    delete ui;
}
///初始化属性结构内容
void NodeTreeDialog::initTreeWidget()
{
    AICCTreeWidget *tw = ui->tw_node;
    tw->clear();
    AICCSqlite sqlite;
    QSqlQuery squery = sqlite.query("select class_name from nodeClass order by sort");
    while(squery.next()){
        QString className = squery.value(0).toString();
        makeRootGroupItem(tw,className,className);
    }

    connect(ui->tw_node,&AICCTreeWidget::itemClicked,this,&NodeTreeDialog::treeWidgetItemClicked);

    tw->expandAll();
}

///初始化工具条上的功能
void NodeTreeDialog::initToolBar(){

}


///创建属性结构的根目录分类
void NodeTreeDialog::makeRootGroupItem(AICCTreeWidget *atw,const QString name,const QString text)
{
    QTreeWidgetItem *rootGroupMathOperations = new QTreeWidgetItem(atw);
    rootGroupMathOperations->setText(0,text);
    rootGroupMathOperations->setData(0,Qt::UserRole+1,QVariant::fromValue(name));
}


///获得DataModelRegistry对象
void NodeTreeDialog::setNodeMap(QMap<QString,QSet<QString>> pnm){
    qDebug() << "setNodeMap: " << pnm.size() << "  QSet size: " << pnm["MathOperations"].size();
    _nodeMap = pnm;
}

///根据名称创建button
AICCToolButton * createToolButton( QString name,QString caption){

    AICCToolButton *tb = new AICCToolButton();
    tb->setText(caption);
    tb->setNodeName(name);
    tb->setNodeCaption(caption);
    tb->setMinimumSize(80,50);
    QSizePolicy sp = tb->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Preferred);
    tb->setSizePolicy(sp);
    return tb;
}

///点击树形节点后右侧按钮区域变化
void NodeTreeDialog::treeWidgetItemClicked(QTreeWidgetItem *item, int column){
    this->setFixedWidth(1000);

    ///删除已有的按钮
    QList<AICCToolButton*> tbs = ui->widget_node->findChildren<AICCToolButton*>();
    ui->widget_node->setSizeIncrement(1000,600);
    foreach(QToolButton *tb,tbs){
        ui->gl_node->removeWidget(tb);
        delete tb;
    }
    ///增加点击分类对应的按钮
    QString itemData = item->data(0,Qt::UserRole+1).value<QString>();
    if(_nodeMap.contains(itemData)){
        AICCSqlite sqlite;
        QSet<QString> nodes = _nodeMap[itemData];
        int i=0;
        foreach(QString name,nodes){
            QSqlQuery squery = sqlite.query("select caption from node where name = '"+name+"'");
            AICCToolButton *tb;
            if(squery.next())
                tb = createToolButton(name,squery.value(0).toString());
            else
                tb = createToolButton(name,name);

            //点击按钮通知事件
            connect(tb,&QToolButton::clicked,this,[tb,this](bool checked=false){
               emit nodeDoubleClicked(tb->text());
            });
            ui->gl_node->addWidget(tb,i/15,i%8,Qt::AlignHCenter);
            i++;
        }
    }
}























