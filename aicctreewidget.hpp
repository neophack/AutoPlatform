#ifndef AICCTREEWIDGET_H
#define AICCTREEWIDGET_H

#include <QTreeWidget>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QDebug>
#include <QSplitter>
#include <QMimeData>
#include <QDrag>
#include <QMenu>


class AICCTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    AICCTreeWidget(QSplitter *parent = nullptr)
    {
        connect(this,&QTreeWidget::customContextMenuRequested,this,&AICCTreeWidget::onTreeWidgetCustomContextMenuRequested);
    }

protected:
    /**
     * 鼠标按下操作
     * @brief mousePressEvent
     * @param event
     */
    void mousePressEvent(QMouseEvent* event)
    {
//        qDebug() << "mouse press";
        if(event->button() && Qt::LeftButton)
        {
            _selectItem = itemAt(event->pos());

            QByteArray dataItem;
            QDataStream dataStream(&dataItem,QIODevice::WriteOnly);
            dataStream << _selectItem->text(0);

            QByteArray dataItemName;
            QDataStream dataStreamName(&dataItemName,QIODevice::WriteOnly);
            QString sidata = _selectItem->data(0,Qt::UserRole+1).toString();
            dataStreamName << sidata;

            if(_selectItem!=Q_NULLPTR && _selectItem->parent()!=Q_NULLPTR && QString::compare(sidata,"")!=0)
            {
                QDrag* drag = new QDrag(this);
                qDebug() << "aicctreewidget.hpp:" << _selectItem->data(0,Qt::UserRole+1).toString();

                QMimeData* mimeData = new QMimeData;
                mimeData->setData("Data/text",dataItem);
                //将要生成的flowview节点的名字代入Data/name字段
                mimeData->setData("Data/name",dataItemName);


                //            QtGuiDrag* dragPiamap = new QtGuiDrag(nullptr);
                //            dragPiamap->setShowText(_selectItem->text(0));
                //            QPixmap pixmap = dragPiamap->grab();


                drag->setMimeData(mimeData);
                drag->exec(Qt::MoveAction);
            }
        }
//        else if(event->button() && Qt::RightButton){
        QTreeWidget::mousePressEvent(event);
//        }

    };
    /**
     * 自定义鼠标右键函数
     * @brief onTreeWidgetCustomContextMenuRequested
     * @param pos
     */
    void onTreeWidgetCustomContextMenuRequested(const QPoint &pos)
    {

        QModelIndex curIndex = this->indexAt(pos);
        qDebug() << curIndex.column()<< " " << curIndex.row();

        if(curIndex.isValid())
        {
            QMenu menu;
            //            menu.addAction(tr("增加"),this,&AICCTreeWidget::onActionAdd);
            menu.addAction(tr("增加"),this,[=](){
                qDebug()<<"onActionAdd:";
            } );
            menu.addSeparator();
            menu.addAction(tr("删除"),this,[=](){
                qDebug()<<"onActionDel";
            });
            menu.exec(QCursor::pos());
        }

    }

private:
    QTreeWidgetItem* _selectItem;
};

#endif // AICCTREEWIDGET_H
