#ifndef AICCFLOWSCENE_H
#define AICCFLOWSCENE_H

#include <nodes/FlowView>
#include <nodes/FlowScene>
#include <QDebug>
#include <QDropEvent>
#include <QStringList>
#include <QMimeData>
#include "qvariant.h"

#include "aiccmodel.hpp"

using QtNodes::FlowView;
using QtNodes::FlowScene;

class AICCFlowView : public FlowView
{
    Q_OBJECT
public:
    AICCFlowView(){}
    AICCFlowView(FlowScene *scene):FlowView(scene,Q_NULLPTR){}

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
//    void dragLeaveEvent(QDragLeaveEvent *e)
//    {
//        qDebug()<<"flow view dragg leave";
//        e->accept();
//    };

//    void startDrag(Qt::DropActions supportedActions){
//        qDebug() << "flow view start drag";
//    };
};

//}
#endif // AICCFLOWSCENE_H
