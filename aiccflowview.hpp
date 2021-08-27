#ifndef AICCFLOWSCENE_H
#define AICCFLOWSCENE_H

#include <nodes/FlowView>
#include <nodes/FlowScene>
#include <nodes/Node>
#include <QDebug>
#include <QDropEvent>
#include <QStringList>
#include <QMimeData>
#include "qvariant.h"

#include "aiccmodel.hpp"

using QtNodes::FlowView;
using QtNodes::FlowScene;
using QtNodes::Node;

class AICCFlowView : public FlowView
{
    Q_OBJECT
public:
    AICCFlowView(){}
    AICCFlowView(FlowScene *scene):FlowView(scene,Q_NULLPTR)
    {
        _scene = scene;
    }

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


            //--------------------------------------------------------------------
                auto type = _scene->registry().create("数据源节点");
                if(type)
                {
                    QtNodes::Node& node = _scene->createNode(std::move(type));
                    QPoint pos = e->pos();
                    QPointF posView = this->mapToScene(pos);
                    node.nodeGraphicsObject().setPos(posView);
                     _scene->nodePlaced(node);
                }


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

private:
    FlowScene* _scene;
};

//}
#endif // AICCFLOWSCENE_H
