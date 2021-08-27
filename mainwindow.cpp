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
#include <aiccsourcedatamodel.hpp>
#include <aiccdisplaydatamodel.hpp>
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
    this->InitTreeView();
    this->InitNodeEditor();
    this->setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setTreeNode(QTreeWidget *tw,const char* ptext,const char* picon){
    QTreeWidgetItem *pItem = new QTreeWidgetItem();
    pItem->setText(0,ptext);
    QIcon icon;
    icon.addPixmap(QPixmap(picon));
    pItem->setIcon(0,icon);

    tw->addTopLevelItem(pItem);
}

void MainWindow::InitTreeView()
{
    AICCTreeWidget *tw = ui->treeWidget;
//    QTreeWidget *tw = ui->treeWidget;
    tw->setHeaderHidden(true);
    tw->setDragDropMode(QAbstractItemView::DragOnly);
    tw->setDragEnabled(true);
    tw->clear();

    setTreeNode(tw,"shebei",":/res/ticon1.png");
    setTreeNode(tw,"ECU",":/res/ticon1.png");
    setTreeNode(tw,"qudong",":/res/ticon1.png");
    setTreeNode(tw,"suanfa",":/res/ticon1.png");
    setTreeNode(tw,"xinhao",":/res/ticon1.png");
    setTreeNode(tw,"IO",":/res/ticon1.png");
}

std::shared_ptr<DataModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<DataModelRegistry>();
      ret->registerModel<AICCDisplayDataModel>("结果数据");
      ret->registerModel<AICCSourceDataModel>("源数据");
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

void MainWindow::InitNodeEditor()
{

    setNodeEditorStyle();
    auto scene = new FlowScene (registerDataModels());
    auto view = new AICCFlowView(scene);
    view->setAcceptDrops(true);
    view->setDragMode(QGraphicsView::DragMode::NoDrag);




    ui->vl_nodeeditor->addWidget(view);
    ui->vl_nodeeditor->setContentsMargins(0,0,0,0);
    ui->vl_nodeeditor->setSpacing(0);

}

//void MainWindow::startDrag(Qt::DropActions supportedActions)
//{
//    qDebug() << "main windows start drag";
//}

//void MainWindow::dragMoveEvent(QDragMoveEvent *event)
//{
//    qDebug() << "main window drag move event";
//}

