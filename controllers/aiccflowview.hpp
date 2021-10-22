#ifndef AICCFLOWSCENE_H
#define AICCFLOWSCENE_H

#include <nodes/FlowView>
#include <nodes/FlowScene>
#include <nodes/Node>
#include <QDebug>
#include <QDropEvent>
#include <QStringList>
#include <QMimeData>
#include <QtCore/QObject>
#include <QMouseEvent>
#include <QMessageBox>
#include "qvariant.h"
#include "aiccmodel.hpp"


using QtNodes::FlowView;
using QtNodes::FlowScene;
using QtNodes::Node;
using QtNodes::NodeGraphicsObject;
using QtNodes::NodeDataModel;

///自定义FlowView
class AICCFlowView : public FlowView
{
    Q_OBJECT
public:
    AICCFlowView(){
    }
    AICCFlowView(FlowScene *scene,QWidget *parent):FlowView(scene,parent)
    {
        _scene = scene;
        connect(_scene,&FlowScene::selectionChanged,this,[&]()
        {
            auto selectedCount = _scene->selectedNodes().size();
            if(selectedCount==1){
                emit getNodeDataModel(_scene->selectedNodes()[0]->nodeDataModel());
            }
            else{
                emit getNodeDataModel(Q_NULLPTR);
            }
        });

    }
public:
Q_SIGNALS:
    void getNodeDataModel(NodeDataModel *nodeDataModel);
    void nodeDoubleClicked(Node& n);
    //该信号需要将view对象以参数方式传递过去使用,否则会有问题
    void checkSubSystemName(const QString &name,const QPoint mousePos,const AICCFlowView *cview);

protected:
    void dragMoveEvent(QDragMoveEvent *e)
    {
        //        qDebug()<<"flow view drag move";
        //        e->accept();
    };
    void dropEvent(QDropEvent *e) {
        QStringList formats = e->mimeData()->formats();
        //        qDebug() << "flow view drop" << formats;
        if(e->mimeData()->hasFormat("Data/name"))
        {
            QByteArray itemData = e->mimeData()->data("Data/name");
            QDataStream dataStream(&itemData,QIODevice::ReadOnly);

            QString text;
            dataStream >> text;
            qDebug() << "text:"<<text;

            //如果当前节点为子系统,通知上层AICCStackedWidget判断是否有重名,是否可创建新的page
            emit checkSubSystemName(text,e->pos(),this);

            //处理消息传递
            if(e->source() == this)
            {
                e->setDropAction(Qt::MoveAction);
                e->accept();
            }else {
                e->acceptProposedAction();
            }
        }
        else
            e->ignore();
    };
public:
    ///在FlowScene中创建node
    void createNode(QString const &name,const QPoint pos) const
    {
        auto type = _scene->registry().create(name);
        if(type){
            QtNodes::Node &node = _scene->createNode(std::move(type));
            QPointF posView = this->mapToScene(pos);
            node.nodeGraphicsObject().setPos(posView);
            _scene->nodePlaced(node);
        }
    }

    FlowScene *scene() const{
        return _scene;
    }

private:
    FlowScene* _scene;
};

//}
#endif // AICCFLOWSCENE_H
