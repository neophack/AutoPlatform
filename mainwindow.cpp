#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QItemDelegate>
#include <QStandardItemModel>
#include <TreeViewReadonlyDelegate.h>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QDrag>
#include <QGraphicsView>
#include <QString>
#include "aiccflowview.hpp"

#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/FlowViewStyle>
#include <nodes/NodeStyle>
#include <nodes/ConnectionStyle>
#include <nodes/DataModelRegistry>
#include <datamodel/aiccsourcedatamodel.hpp>
#include <datamodel/aiccdisplaydatamodel.hpp>
#include <calculator/aicccalculator.hpp>
#include <aiccmodel.hpp>

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::FlowViewStyle;
using QtNodes::NodeStyle;
using QtNodes::ConnectionStyle;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);

//    ui->splitter->setOpaqueResize(false);
//    ui->splitter->setStretchFactor(0,2);
//    ui->splitter->setStretchFactor(1,6);
//    ui->splitter->setStretchFactor(2,2);


    this->initMenu();
    this->initTreeView();
    this->initNodeEditor();
    this->setAcceptDrops(true);
    this->initSplitter();
    this->initTableWidget();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenu()
{
    connect(ui->actionExit,&QAction::triggered,this,&QWidget::close);
    connect(ui->actionNodeWindow,&QAction::toggled,ui->dw_left,&QDockWidget::setVisible);
    connect(ui->actionPropertyWindow,&QAction::toggled,ui->dw_right,&QDockWidget::setVisible);
    connect(ui->actionAbout,&QAction::triggered,this,&QApplication::aboutQt);
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
    itemSource1->setText(0,"设备");
    QTreeWidgetItem* itemSource2 = new QTreeWidgetItem(rootGroupSource);
    itemSource2->setText(0,"ECU");
    QTreeWidgetItem* itemSourceCalculator = new QTreeWidgetItem(rootGroupSource);
    itemSourceCalculator->setText(0,"四则运算源数据");
    itemSourceCalculator->setData(0,Qt::UserRole+1,"AICCNumberSource");


    QTreeWidgetItem* rootGroupProcess = new QTreeWidgetItem(tw);
    rootGroupProcess->setText(0,QStringLiteral("过程"));
    QTreeWidgetItem* itemProcess1 = new QTreeWidgetItem(rootGroupProcess);
    itemProcess1->setText(0,"驱动");

    QTreeWidgetItem* itemProcess2 = new QTreeWidgetItem(rootGroupProcess);
    itemProcess2->setText(0,"算法");
    QTreeWidgetItem* itemProcessCalculatorAddition = new QTreeWidgetItem(itemProcess2);
    itemProcessCalculatorAddition->setText(0,"加法");
    itemProcessCalculatorAddition->setData(0,Qt::UserRole+1,"AICCAdditionOperation");
    QTreeWidgetItem* itemProcessCalculatorSubstraction = new QTreeWidgetItem(itemProcess2);
    itemProcessCalculatorSubstraction->setText(0,"减法");
    itemProcessCalculatorSubstraction->setData(0,Qt::UserRole+1,"AICCSubtractionOperation");
    QTreeWidgetItem* itemProcessCalculatorMultiplication = new QTreeWidgetItem(itemProcess2);
    itemProcessCalculatorMultiplication->setText(0,"乘法");
    itemProcessCalculatorMultiplication->setData(0,Qt::UserRole+1,"AICCMultiplicationOperation");
    QTreeWidgetItem* itemProcessCaculatorDivision = new QTreeWidgetItem(itemProcess2);
    itemProcessCaculatorDivision->setText(0,"除法");
    itemProcessCaculatorDivision->setData(0,Qt::UserRole+1,"AICCDivisionOperation");

    QTreeWidgetItem* itemProcess3 = new QTreeWidgetItem(rootGroupProcess);
    itemProcess3->setText(0,"信号");
    QTreeWidgetItem* itemProcess4 = new QTreeWidgetItem(rootGroupProcess);
    itemProcess4->setText(0,"IO");


    QTreeWidgetItem* rootGroupResult = new QTreeWidgetItem(tw);
    rootGroupResult->setText(0,QStringLiteral("数据目标"));
    QTreeWidgetItem* itemResultCalculator = new QTreeWidgetItem(rootGroupResult);
    itemResultCalculator->setText(0,"四则运算结果");
    itemResultCalculator->setData(0,Qt::UserRole+1,"AICCNumberResult");

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

std::shared_ptr<DataModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<DataModelRegistry>();
      ret->registerModel<AICCDisplayDataModel>("结果数据");
      ret->registerModel<AICCSourceDataModel>("源数据");
      ret->registerModel<AICCNumberSourceDataModel>("四则运算");
      ret->registerModel<AICCNumberResultDataModel>("四则运算");
      ret->registerModel<AICCAdditionModel>("四则运算");
      ret->registerModel<AICCSubtractionModel>("四则运算");
      ret->registerModel<AICCMultiplicationModel>("四则运算");
      ret->registerModel<AICCDivisionModel>("四则运算");
    return ret;
}

void setNodeEditorStyle()
{
    FlowViewStyle::setStyle(
    R"(
    {
      "FlowViewStyle": {
        "BackgroundColor": [255, 255, 240],
        "FineGridColor": [245, 245, 230],
        "CoarseGridColor": [235, 235, 220]
      }
    }
    )");

    NodeStyle::setNodeStyle(
    R"(
    {
      "NodeStyle": {
        "NormalBoundaryColor": "darkgray",
        "SelectedBoundaryColor": "deepskyblue",
        "GradientColor0": "mintcream",
        "GradientColor1": "mintcream",
        "GradientColor2": "mintcream",
        "GradientColor3": "mintcream",
        "ShadowColor": [200, 200, 200],
        "FontColor": [10, 10, 10],
        "FontColorFaded": [100, 100, 100],
        "ConnectionPointColor": "white",
        "PenWidth": 2.0,
        "HoveredPenWidth": 2.5,
        "ConnectionPointDiameter": 10.0,
        "Opacity": 1.0
      }
    }
    )");

    ConnectionStyle::setConnectionStyle(
    R"(
    {
      "ConnectionStyle": {
        "ConstructionColor": "gray",
        "NormalColor": "black",
        "SelectedColor": "gray",
        "SelectedHaloColor": "deepskyblue",
        "HoveredColor": "deepskyblue",

        "LineWidth": 3.0,
        "ConstructionLineWidth": 2.0,
        "PointDiameter": 10.0,

        "UseDataDefinedColors": false
      }
    }
    )");
}

void MainWindow::initNodeEditor()
{
//    QTableWidget * tw = ui->tableWidget;
    QVBoxLayout *vbl = ui->vl_nodeeditor;
    setNodeEditorStyle();
    auto scene = new FlowScene (registerDataModels());
    auto view = new AICCFlowView(scene);
    view->setAcceptDrops(true);
    view->setDragMode(QGraphicsView::DragMode::NoDrag);
    connect(view,&AICCFlowView::getNodeDataModel,this,[&](NodeDataModel *nodeDataModel)
    {
        QTableWidget * tw = ui->tableWidget;
        tw->setRowCount(0);
        if(nodeDataModel==Q_NULLPTR) return;
        tw->setRowCount(tw->rowCount()+1);
        tw->setItem(0,0,new QTableWidgetItem("caption"));
        tw->setItem(0,1,new QTableWidgetItem(nodeDataModel->caption()));

        tw->setRowCount(tw->rowCount()+1);
        tw->setItem(1,0,new QTableWidgetItem("name"));
        tw->setItem(1,1,new QTableWidgetItem(nodeDataModel->name()));

        qDebug() << "emit getNodeDataModel";
    });

    vbl->addWidget(view);
    vbl->setContentsMargins(0,0,0,0);
    vbl->setSpacing(0);
}

void MainWindow::initSplitter()
{
//    ui->splitter->setStretchFactor(0,0);
//    ui->splitter->setStretchFactor(1,10);
//    ui->splitter->setStretchFactor(2,0);
}


void MainWindow::initTableWidget()
{
    ui->tableWidget->verticalHeader()->setHidden(true);
}
