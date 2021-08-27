#ifndef AICCTREEWIDGET_H
#define AICCTREEWIDGET_H

#include <QTreeWidget>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QDebug>
#include <QSplitter>
#include <QMimeData>
#include <QDrag>

class AICCTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    AICCTreeWidget(QSplitter *parent = nullptr){}

protected:
    void mousePressEvent(QMouseEvent* event)
    {
        qDebug() << "mouse press";
        if(event->button()&Qt::LeftButton)
        {
            _selectItem = itemAt(event->pos());
            QByteArray dataItem;
            QDataStream dataStream(&dataItem,QIODevice::WriteOnly);
            dataStream << _selectItem->text(0);

            QMimeData* mimeData = new QMimeData;
            mimeData->setData("Data/name",dataItem);

//            QtGuiDrag* dragPiamap = new QtGuiDrag(nullptr);
//            dragPiamap->setShowText(_selectItem->text(0));
//            QPixmap pixmap = dragPiamap->grab();

            QDrag* drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->exec(Qt::MoveAction);
        }
        QTreeWidget::mousePressEvent(event);
    };
//    void dragMoveEvent(QDragMoveEvent* event)
//    {
//        qDebug()<< "drag move";
//    };
private:
    QTreeWidgetItem* _selectItem;
};

#endif // AICCTREEWIDGET_H
