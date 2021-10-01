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

    //输入部分
    QTreeWidgetItem *rootGroupInput = new QTreeWidgetItem(tw);
    rootGroupInput->setText(0,QStringLiteral("输入"));

    //控制部分
    QTreeWidgetItem *rootGroupControl = new QTreeWidgetItem(tw);
    rootGroupControl->setText(0,QStringLiteral("控制"));
    QTreeWidgetItem *itemMath = new QTreeWidgetItem(rootGroupControl);
    itemMath->setText(0,QStringLiteral("数学计算"));
    //    connect(ui->tw_node,&QTreeWidget::itemClicked,ui->gl_node,[&,this](QTreeWidgetItem *item,int column ){
    //        if(item->text(0)==QString::fromStdString("数学计算")){
    //            QList<QToolButton*> tbs = ui->gl_node->findChildren<QToolButton*>();
    //            foreach(QToolButton *tb,tbs){
    //                delete tb;
    //            }

    //            if(_nodeMap.contains("数学计算"))
    //            {
    //                QSet<QString> nodes = _nodeMap["数学计算"];
    //                int i = 0;
    //                foreach( QString name,nodes){
    //                    QToolButton *tb = createToolButton(name);
    //                    connect(tb,&QToolButton::clicked,this,[&](bool checked = false){
    //                        emit this->nodeDoubleClicked(tb->text());
    //                    });
    //                    ui->gl_node->addWidget(tb,i/4,i%4,Qt::AlignHCenter);
    //                    i++;
    //                    qDebug() << "数学计算" << _nodeMap["数学计算"].toList().size() << endl;
    //                }

    //            }
    //        }
    //    });

    //    connect(ui->tw_node,SIGNAL(AICCTreeWidget::itemClicked(QTreeWidgetItem*item, int column)),this,SLOT(NodeTreeDialog::treeWidgetItemClicked(QTreeWidgetItem* item, int column)));
    //       connect(ui->tw_node, SIGNAL(QTreeWidget::itemClicked()),ui->gl_node,SLOT(NodeTreeDialog::makeToolButtons()));
    //    connect(ui->tw_node, &QTreeWidget::itemClicked,ui->gl_node,&NodeTreeDialog::makeToolButtons);
    connect(ui->tw_node,&AICCTreeWidget::itemClicked,this,&NodeTreeDialog::treeWidgetItemClicked);


    //结果部分
    QTreeWidgetItem *rootGroupResult = new QTreeWidgetItem(tw);
    rootGroupResult->setText(0,QStringLiteral("结果"));

    tw->expandAll();
}

///加载node的数据
void NodeTreeDialog::initNodeConfig()
{}

///获得DataModelRegistry对象
void NodeTreeDialog::setNodeMap(QMap<QString,QSet<QString>> pnm){
    qDebug() << "setNodeMap: " << pnm.size() << "  QSet size: " << pnm["数学计算"].size();
    _nodeMap = pnm;
}

///根据名称创建button
QToolButton * createToolButton( QString name){

    QToolButton *tb = new QToolButton();
    tb->setText(name);
    tb->setMinimumSize(100,100);
    QSizePolicy sp = tb->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    tb->setSizePolicy(sp);
    return tb;
}

//void NodeTreeDialog::makeToolButtons(QTreeWidgetItem *item,int column )
//{

//}

void NodeTreeDialog::treeWidgetItemClicked(QTreeWidgetItem *item, int column){
    if(item->text(0)==QString::fromStdString("数学计算")){
        QList<QToolButton*> tbs = ui->gl_node->findChildren<QToolButton*>();
        foreach(QToolButton *tb,tbs){
            delete tb;
        }

        if(_nodeMap.contains("数学计算"))
        {
            QSet<QString> nodes = _nodeMap["数学计算"];
            int i = 0;
            foreach( QString name,nodes){
                QToolButton *tb = createToolButton(name);

                //点击按钮通知事件
                connect(tb,&QToolButton::clicked,this,[tb,this](bool checked = false){
                    emit nodeDoubleClicked(tb->text());
                });

//                connect(tb,&QToolButton::clicked,this,&NodeTreeDialog::emitNodeClicked);
                ui->gl_node->addWidget(tb,i/4,i%4,Qt::AlignHCenter);
                i++;
                qDebug() << "数学计算" << _nodeMap["数学计算"].toList().size() << endl;
            }

        }
    }
}

//void NodeTreeDialog::emitNodeClicked(bool checked,QString name){
//    emit nodeDoubleClicked("name");
//}





















