#ifndef AICCSTACKEDWIDGET_H
#define AICCSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QMap>
#include <QSet>
#include <QStackedLayout>
#include <QPushButton>

#include <utils.h>

#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/FlowViewStyle>
#include <nodes/NodeStyle>
#include <nodes/ConnectionStyle>
#include <nodes/DataModelRegistry>

#include <nodeparser/module_library.hpp>
#include <controllers/aiccflowview.hpp>

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::FlowViewStyle;
using QtNodes::NodeStyle;
using QtNodes::ConnectionStyle;

class AICCStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    AICCStackedWidget(QWidget *parent=nullptr){
        _moduleLibrary = new ModuleLibrary();
        this->setNodeEditorStyle();
        _currPagePathName = "/root";
    };

    ~AICCStackedWidget(){
        delete _moduleLibrary;
    }

    ///设置NodeEditor的样式
    void setNodeEditorStyle()
    {
        FlowViewStyle::setStyle(
                    R"(
        {
          "FlowViewStyle": {
            "BackgroundColor": [255, 205, 255],
            "FineGridColor": [255, 255, 255],
            "CoarseGridColor": [255, 255, 255]
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
            "LineWidth": 1.0,
            "ConstructionLineWidth": 2.0,
            "PointDiameter": 10.0,
            "UseDataDefinedColors": false
          }
        }
        )");
    }

    ///注册右键数据模型并返回该数据模型给FlowScene
    std::shared_ptr<DataModelRegistry> registerDataModels()
    {
        auto ret = std::make_shared<DataModelRegistry>();

        const QString path = "/home/fc/works/QtProjects/AutoPlatform/AutoPlateform/nodeconfig/";
        QStringList files = getFlieList(path);

        _moduleLibrary->importFiles(files);
        std::vector<Invocable> invocableList = _moduleLibrary->getInvocableList();

        for(long int unsigned i=0;i<invocableList.size();i++){
            const auto &inv = invocableList[i];
            auto f = [inv](){return std::make_unique<InvocableDataModel>(inv);};
            //        ret->registerModel<MyDataModel>(f,QString::fromStdString(inv.getName()));
            //math.hpp的内容注册为MathOperations分类的内容
            ret->registerModel<MyDataModel>(f,"MathOperations");

            //此处包含了MathOperations中包含了多少个按钮
            //node模块的按钮生成根据该数据生成
            QSet<QString> category;
            category = _nodeCategoryMap.value("MathOperations");
            category.insert(QString::fromStdString(inv.getName()));
            _nodeCategoryMap.insert("MathOperations",category);


            // TODO:后续继续增加其他分类

        }
        //注册完数据模型后发出通知，由NodeTreeDialog窗口去接收消息，在NodeTreeDialog左侧展示刚刚注册的数据项
        emit registerDataModelsCompleted(_nodeCategoryMap);
        return ret;
    }


    /**
     * 增加一个新的page，并初始化一个FlowScene
     * @brief addNewPageFlowScene
     * @param pageName 该参数为新增的page对应的管理名称，一般为子系统的全路径+名称
     */
    void addNewPageFlowScene(QString pageName){
        //设置nodeeditor的scene与view
        auto scene = new FlowScene (this->registerDataModels());
        auto view = new AICCFlowView(scene,this);
        view->setAcceptDrops(true);
        view->setDragMode(QGraphicsView::DragMode::NoDrag);

        //接受view的node创建完成消息增加新的page
        connect(view,&AICCFlowView::checkSubSystemName,this,[&](const QString &name,const QPoint pos,const AICCFlowView *cview){
            //如果为其他普通节点,直接通知FlowView创建节点
            if(name!="subsystem::SubSystem"){
                cview->createNode(name,pos);
                return;
            }else{
                if(_routeDataMap.contains(_currPagePathName+"/"+name)){
                    QMessageBox::warning(NULL,"警告","当前要创建的子系统已存在,请重新命名子系统!",QMessageBox::Ok,QMessageBox::Ok);
                    return;
                }
                cview->createNode(name,pos);
                this->addNewPageFlowScene(name);
            }
        });

        //双击节点显示节点的属性窗口
        connect(view,&AICCFlowView::nodeDoubleClicked,this,[&](Node &n){
            //如果为子系统,显示子系统对应的窗口
            if(n.nodeDataModel()->name()=="subsystem::SubSystem"){
                _currPagePathName += ("/"+n.nodeDataModel()->name());
                emit notifyCurrentPagePathNameChanged(_currPagePathName);
            }
            // 此处要修改为向外发送消息，由主窗口来处理双击后的操作，以调用npDialog
            emit nodeDoubleClicked(n.nodeDataModel(), _currPagePathName);

        });

        //获得节点属性,发送消息至外层继续将节点属性数据传递到主窗口
        connect(view,&AICCFlowView::getNodeDataModel,this,[&](NodeDataModel *nodeDataModel){
            emit getNodeDataModel(nodeDataModel);
        });

        //双击libarary browser窗口中左侧的树形item，在FlowScene添加对应的node（当前停用，改为了拖动形式）
//        connect(nodeTreeDialog,&NodeTreeDialog::nodeDoubleClicked,this,[&](QString name){
            //此处可在view中创建node
//            _aiccFlowView->createNode(name,QPoint(_flowScene->width()/2,_flowScene->height()/2));

//            qDebug() << "node tree dialog clicked:" << name << endl;
//        });



        //新增page页面,增加新的路径到路由数据集中,并设置当前页面的路径,通知导航条更新路径
        this->addWidget(view);
        _routeDataMap.insert(_currPagePathName+"/"+pageName,this->count()-1);
//        _currPagePathName = _currPagePathName + "/"+pageName;

        qDebug() << _routeDataMap;
    }

    void setCurrentUrl(const QString &url){
        this->setCurrentIndex(this->_routeDataMap[url]);
    }

public:
    const QMap<QString, int> &routeDataMap() const;
    void setCurrPagePathName(const QString &newCurrPagePathName);

Q_SIGNALS:
    //注册完DataModels发送消息
    void registerDataModelsCompleted(const QMap<QString,QSet<QString>> nodeMap);
    //传递FlowView的getNodeDataModel到外层
    void getNodeDataModel(NodeDataModel *nodeDataModel);
    //双击节点后发送节点消息到外层，当前是为属性窗口提供信息
    void nodeDoubleClicked(NodeDataModel *nodeDataModel,const QString &pagePathName);
    //通知FlowView创建节点
    void notifyCreateNode(const QString nodeName);

    //最终改造,_currPagePathName改变时向外通知消息
    void notifyCurrentPagePathNameChanged(const QString &url);

private:
//    QMap<QString,int> _pages;
    //模块分类数据
    QMap<QString,QSet<QString>> _nodeCategoryMap;
    //nodeeditor部分
    ModuleLibrary *_moduleLibrary;
//    StackedWidgetRouteData *_swRouteData;

    //当前page路径名称,形式为"/root/level1/level2"
    QString _currPagePathName;
    //key为当前page的路由，value为page对应的index
    QMap<QString,int> _routeDataMap;

};

inline const QMap<QString, int> &AICCStackedWidget::routeDataMap() const
{
    return _routeDataMap;
}

inline void AICCStackedWidget::setCurrPagePathName(const QString &newCurrPagePathName)
{
    _currPagePathName = newCurrPagePathName;
    emit notifyCurrentPagePathNameChanged(_currPagePathName);
}

#endif // AICCSTACKEDWIDGET_H
