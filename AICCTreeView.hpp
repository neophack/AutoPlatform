#ifndef AICCTREEVIEW_H
#define AICCTREEVIEW_H
#include <QDebug>
#include <QTreeView>
#include <QSplitter>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QStringList>
#include <QMimeData>


class AICCTreeView : public QTreeView
{
    Q_OBJECT
public:
    AICCTreeView(){}
    AICCTreeView(QSplitter *splitter){}

protected:
//    void dragMoveEvent(QDragMoveEvent *e)
//    {
//        qDebug()<<"aicc view drag move";

//    };
//    void dropEvent(QDropEvent *e) {
//        QStringList formats = e->mimeData()->formats();
//        for(int i=0;i<formats.size();i++){
//            qDebug() << formats.at(i);
//        }

//        qDebug() << "aicc view drop" << formats;
//    };
//    void dragLeaveEvent(QDragLeaveEvent *e)
//    {
//        qDebug()<<"aicc view dragg leave";

//    };


//    void dragMoveEvent(QDragMoveEvent *e)
//    {
//        qDebug() << "AICCTreeView drag move event";
//    }

//    void dragEnterEvent(QDragEnterEvent *e)
//    {
//        qDebug() << "AICCTreeView drag enter event";

//    }

//    void dragLeaveEvent(QDragLeaveEvent *event)
//    {
//        qDebug() << "AICCTreeView drag leave event";
//    }
//    void startDrag(Qt::DropActions suportedActions)
//    {
//        qDebug() << "AICCTreeView start drag";
//    }
};

#endif // AICCTREEVIEW_H
