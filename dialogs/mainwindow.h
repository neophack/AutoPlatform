#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTableWidget>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <itemreadonlydelegate.h>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QDrag>
#include <QGraphicsView>
#include <QString>
#include <QStackedLayout>
#include <QSharedPointer>

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
#include <controllers/aiccflowview.hpp>
#include <controllers/aiccstackedwidget.hpp>
#include <dialogs/projectdialog.h>
#include <dialogs/nodeparametersdialog.h>
#include <dialogs/nodetreedialog.h>
#include "stdio.h"
#include "utils.h"
#include "aicctreewidget.hpp"
#include "controllers/aicctoolbutton.hpp"
//#include "controllers/aiccbreadcrumbnavigation.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::FlowViewStyle;
using QtNodes::NodeStyle;
using QtNodes::ConnectionStyle;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
//    void startDrag(Qt::DropActions supportedActions);
//    void dragMoveEvent(QDragMoveEvent *e);

private:
    Ui::MainWindow *ui;
    ProjectDialog *projectDialog;
    NodeParametersDialog *npDialog;
    NodeTreeDialog *nodeTreeDialog;

//    FlowScene *_flowScene;
//    AICCFlowView *_aiccFlowView;

    //nodeeditor部分
    ModuleLibrary *moduleLibrary;
    QMap<QString,QSet<QString>> nodeMap;

    AICCStackedWidget asw;

    void initMenu();
    void initTreeView();
    //nodeeditor调用部分
//    void initNodeEditor();
//    AICCFlowView * makeNewNodeEditorScene();
//    std::shared_ptr<DataModelRegistry> registerDataModels();

    void fillTableData(QTableWidget *tw,const NodeDataModel *nmd);

    void initSplitter();
    void initTableWidget();
    void initToolbar();
    void setTreeNode(QTreeWidget *tw,const char* ptext,const char* picon);
    void initBreadcrumbNavigation();
    void initStackedWidget();


};
#endif // MAINWINDOW_H
