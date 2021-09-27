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

class AICCFlowView : public FlowView
{
    Q_OBJECT
public:
    AICCFlowView(){
    }
    AICCFlowView(FlowScene *scene):FlowView(scene,Q_NULLPTR)
    {
        _scene = scene;
        connect(_scene,&FlowScene::selectionChanged,this,[&]()
        {
            auto selectedCount = _scene->selectedNodes().size();
            if(selectedCount==1)
            {
                emit getNodeDataModel(_scene->selectedNodes()[0]->nodeDataModel());
            }
            else
            {
                emit getNodeDataModel(Q_NULLPTR);
            }
        });

        connect(_scene,&FlowScene::nodeDoubleClicked,this,[&](Node& n)
        {
            emit nodeDoubleClicked(n);
        });
    }
public:
Q_SIGNALS:
    void getNodeDataModel(NodeDataModel *nodeDataModel);
    void nodeDoubleClicked(Node& n);

protected:
    void dragMoveEvent(QDragMoveEvent *e)
    {
//        qDebug()<<"flow view drag move";
//        e->accept();
    };
    void dropEvent(QDropEvent *e) {
        QStringList formats = e->mimeData()->formats();
        qDebug() << "flow view drop" << formats;
        if(e->mimeData()->hasFormat("Data/name"))
        {
            QByteArray itemData = e->mimeData()->data("Data/name");
            QDataStream dataStream(&itemData,QIODevice::ReadOnly);

            QString text;
            dataStream >> text;

            qDebug() << "text:"<<text;

            if(QString::compare(text,"AICCNumberSource")==0 || QString::compare(text,"AICCNumberResult")==0
                    || QString::compare(text,"AICCAdditionOperation")==0 || QString::compare(text,"AICCSubtractionOperation")==0
                    || QString::compare(text,"AICCMultiplicationOperation")==0 || QString::compare(text,"AICCDivisionOperation")==0)
                AICCFlowView::createNode(text,e->pos());



            if(e->source() == this)
            {
                e->setDropAction(Qt::MoveAction);
                e->accept();
            }else {
                e->acceptProposedAction();
            }

//            QTreeWidgetItem *item = itemAt(event->pos());
//            if(item==nullptr) return;


        }
        else
            e->ignore();
    };

    void createNode(QString const &name,QPoint pos)
    {
        auto type = _scene->registry().create(name);
        if(type){
            QtNodes::Node &node = _scene->createNode(std::move(type));
            QPointF posView = this->mapToScene(pos);
            node.nodeGraphicsObject().setPos(posView);
            _scene->nodePlaced(node);
        }
    }

private:
    FlowScene* _scene;
};

//}
#endif // AICCFLOWSCENE_H
