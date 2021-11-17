#ifndef AICCSTACKEDWIDGET_H
#define AICCSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QMap>
#include <QSet>
#include <QStackedLayout>
#include <QPushButton>
#include <QDebug>
#include <QString>

#include <utils.h>

#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/FlowViewStyle>
#include <nodes/NodeStyle>
#include <nodes/ConnectionStyle>
#include <nodes/DataModelRegistry>

#include <algorithm>
#include <nodeparser/module_library.hpp>
#include <nodeparser/invocable_parser.hpp>
#include <controllers/aiccflowview.hpp>
#include <sqlite/aiccsqlite.hpp>


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
        this->setNodeEditorStyle();
        _currPagePathName = "/root";

    };

    ~AICCStackedWidget(){
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

    /**
     * 增加一个新的page，并初始化一个FlowScene
     * @brief addNewPageFlowScene
     * @param pageName 该参数为新增的page对应的管理名称，一般为子系统的全路径+名称
     */
    void addNewPageFlowScene(QString pageName){

        //设置nodeeditor的scene与view
        auto scene = new FlowScene();
        auto view = new AICCFlowView(scene,this);
        view->setAcceptDrops(true);
        view->setDragMode(QGraphicsView::DragMode::NoDrag);
        _allViews.push_front(view);

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
        connect(scene,&FlowScene::nodeDoubleClicked,this,[&](Node &n){
            //如果为子系统,显示子系统对应的窗口
            if(n.nodeDataModel()->name()=="subsystem::SubSystem"){
                setCurrPagePathName(_currPagePathName+"/"+n.nodeDataModel()->name());
            }
            // 此处要修改为向外发送消息，由主窗口来处理双击后的操作，以调用npDialog
            emit nodeDoubleClicked(n.nodeDataModel(), _currPagePathName);
        });


        //节点被删除事件响应
        connect(scene,&FlowScene::nodeDeleted,this,[&](Node &n){
            // TODO
            //1:删除当前page下的所有子page
            //2:当删除的SubSystem中包含子SubSystem时要考虑递归删除
            //3:删除routeMap中所有的子路径

            //1.获得要删除的子系统的路径
            QString deletePathName = this->_currPagePathName+"/"+n.nodeDataModel()->name();
            QMap<QString,int>::iterator it = this->_routeDataMap.begin();
            while(it!=this->_routeDataMap.end()){
                QString key = it.key();
                QStringList qsl = key.split(deletePathName);
                qDebug() << "delete path name:" << deletePathName << "key:" << key << "qsl:" << qsl;
                it++;
            }
        });


        //获得节点属性,发送消息至外层继续将节点属性数据传递到主窗口
        connect(view,&AICCFlowView::getNodeDataModel,this,[&](NodeDataModel *nodeDataModel){
            emit getNodeDataModel(nodeDataModel);
        });

        //新增page页面,增加新的路径到路由数据集中,并设置当前页面的路径,通知导航条更新路径
        this->addWidget(view);
        _routeDataMap.insert(_currPagePathName+"/"+pageName,this->count()-1);

    }

    void setCurrentUrl(const QString &url){
        this->setCurrentIndex(this->_routeDataMap[url]);
    }

private:
    ///填充nodeCategoryMap数据
    void insertNodeCategoryMap(const QString className,const QString nodeName){
        QSet<QString> category;
        category = _nodeCategoryMap.value(className);
        category.insert(nodeName);
        _nodeCategoryMap.insert(className,category);
    }


public:
    void setCurrPagePathName(const QString &newCurrPagePathName){
        _currPagePathName = newCurrPagePathName;
        emit notifyCurrentPagePathNameChanged(_currPagePathName);
    }

    const QList<AICCFlowView *> &allViews() const{return _allViews;}
    ///通过key获得view
    AICCFlowView* getView(QString key){
        int index = _routeDataMap[key];
        return _allViews[index];
    }
    ///将当前的scene恢复成默认初始一个主scene状态
    void initDefaultScenes(){
        int rootIndex = 0;
        //1.处理_routeDataMap
        for(auto miter = _routeDataMap.begin();miter!=_routeDataMap.end();){
            if(miter.key().compare("/root/")!=0){
                miter = _routeDataMap.erase(miter);
            }else{
                rootIndex = miter.value();
                miter++;
            }
        }
        //2.处理_allScenes
        for(int i=0;i<_allViews.count();i++){
            if(i==rootIndex){
                _allViews[i]->scene()->clearScene();
               _allViews[i]->scaleDefault();
            }
            else
                //TODO:此处需要研究一下是否需要对view、scene进行回收
                _allViews.removeAt(i);
        }
    }

Q_SIGNALS:
    //注册完DataModels发送消息
    void registerDataModelsCompleted(const QMap<QString,QSet<QString>> nodeMap);
    //传递FlowView的getNodeDataModel到外层
    void getNodeDataModel(NodeDataModel *nodeDataModel);
    //双击节点后发送节点消息到外层，当前是为属性窗口提供信息
    void nodeDoubleClicked(NodeDataModel *nodeDataModel,const QString &pagePathName);

    //最终改造,_currPagePathName改变时向外通知消息
    void notifyCurrentPagePathNameChanged(const QString &url);

private:

    //模块分类数据
    QMap<QString,QSet<QString>> _nodeCategoryMap;
    //当前page路径名称,形式为"/root/level1/level2"
    QString _currPagePathName;
    //key为当前page的路由，value为page对应的index
    QMap<QString,int> _routeDataMap;
    //保存所有FlowScene用于统一操作
//    QList<FlowScene*> _allScenes;
    QList<AICCFlowView *> _allViews;
};


#endif // AICCSTACKEDWIDGET_H
