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
    connect(ui->tw_node,&QTreeWidget::itemClicked,ui->gl_node,[&](QTreeWidgetItem *item,int column )
    {
        if(item->text(0)==QString::fromStdString("数学计算")){
            QList<QToolButton*> tbs = ui->gl_node->findChildren<QToolButton*>();
            foreach(QToolButton *tb,tbs){
                delete tb;
            }

            CategoriesSet cs = _dataModelRegistry->categories();


//            std::set<DataModelRegistry>::iterator it;
//            for(it  =  cs.begin(); it != cs.end(); it++){

//            }

            auto csfind = cs.find(QString::fromStdString("数学计算1"));
            if(csfind != cs.end())
            {
//                csfind.
                //                csfind
            }
            else
            {
                qDebug() << "未发现";
            }
        }
    });
    //    connect(this,&NodeTreeDialog::filesSelected,ui->tw_node,[&](const QStringList &files)
    //    {
    //        qDebug() << files;
    //    });


    //结果部分
    QTreeWidgetItem *rootGroupResult = new QTreeWidgetItem(tw);
    rootGroupResult->setText(0,QStringLiteral("结果"));

    tw->expandAll();
}

///加载node的数据
void NodeTreeDialog::initNodeConfig()
{



}

///获得DataModelRegistry对象
void NodeTreeDialog::setDataModelRegistry( std::shared_ptr<DataModelRegistry> pdmr){
    _dataModelRegistry = pdmr;
}
























