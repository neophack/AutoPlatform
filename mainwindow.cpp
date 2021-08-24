#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QItemDelegate>
#include <QStandardItemModel>
#include <tree_view_readonly_delegate.h>

#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/FlowViewStyle>
#include <nodes/NodeStyle>
#include <nodes/ConnectionStyle>
#include <nodes/DataModelRegistry>
//#include "nodes/internal/TextSourceDataModel.hpp"
//#include "nodes/internal/TextDisplayDataModel.hpp"


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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::InitTreeView()
{
    QStandardItemModel* model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("资源"));
    QList<QStandardItem*> items_first;
    //        QStandardItem* item_device,item_ecu,item_drive,item_algorithm,item_signal,item_IO;
    QStandardItem* item_device = new QStandardItem(QIcon(":/res/ticon1.png"),QStringLiteral("设备"));
    QStandardItem* item_ecu = new QStandardItem(QIcon(":/res/ticon1.png"),QStringLiteral("ECU"));
    QStandardItem* item_drive = new QStandardItem(QIcon(":/res/ticon1.png"),QStringLiteral("驱动"));
    QStandardItem* item_algorithm = new QStandardItem(QIcon(":/res/ticon1.png"),QStringLiteral("算法"));
    QStandardItem* item_signal = new QStandardItem(QIcon(":/res/ticon1.png"),QStringLiteral("信号"));
    QStandardItem* item_IO = new QStandardItem(QIcon(":/res/ticon1.png"),QStringLiteral("IO"));

    items_first.append(item_device);
    items_first.append(item_ecu);
    items_first.append(item_drive);
    items_first.append(item_algorithm);
    items_first.append(item_signal);
    items_first.append(item_IO);


    ReadOnlyDelegate* readOnly = new ReadOnlyDelegate(ui->treeView);

    for(int i=0;i<items_first.size();i++){
        model->appendRow(items_first.at(i));
        ui->treeView->setItemDelegateForRow(i,readOnly);
    }
    ui->treeView->setModel(model);
}

std::shared_ptr<DataModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<DataModelRegistry>();
    //  ret->registerModel<TextSourceDataModel>();
    //  ret->registerModel<TextDisplayDataModel>();
    return ret;
}

//void setNodeEditorStyle(FlowView *fv)
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
    auto view = new FlowView(scene);

    ui->vl_nodeeditor->addWidget(view);
    ui->vl_nodeeditor->setContentsMargins(0,0,0,0);
    ui->vl_nodeeditor->setSpacing(0);
}

