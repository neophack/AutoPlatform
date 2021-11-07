#ifndef AICCTOOLBUTTON_H
#define AICCTOOLBUTTON_H

#include <QToolButton>
#include <QMouseEvent>
#include <QDebug>
#include <QDrag>
#include <QMimeData>

class AICCToolButton : public QToolButton
{
    Q_OBJECT
public:
    AICCToolButton(QWidget *parent=nullptr):QToolButton(parent){};
    void setNodeName(QString name){_nodeName = name;}
    void setNodeCaption(QString caption){_nodeCaption = caption;}
protected:
    void mousePressEvent(QMouseEvent *e)
    {
        if(e->button() & Qt::LeftButton){
            QByteArray dataItemName;
            QDataStream dataStreamName(&dataItemName,QIODevice::WriteOnly);
            dataStreamName << _nodeName;

            QByteArray dataItemCaption;
            QDataStream dataStreamCaption(&dataItemCaption,QIODevice::WriteOnly);
            QString sidataCaption = _nodeCaption;
            dataStreamCaption << sidataCaption;

            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData();
            mimeData->setData("Data/name",dataItemName);
            mimeData->setData("Data/caption",dataItemCaption);

            drag->setMimeData(mimeData);
            drag->exec(Qt::MoveAction);
        }

//        qDebug() << "mouse press event" << dataItem << " "<< dataItemName;
        e->accept();
    }
    void mouseReleaseEvent(QMouseEvent *e)
    {
        qDebug() << "mouse release event";
        e->accept();
    };
    void mouseMoveEvent(QMouseEvent *e)
    {
        qDebug() << "mouse move event";
        e->accept();
    };

signals:
    void preperNewTestButton();
private slots:

private:
    QPoint _pressPoint;
    QString _nodeName;
    QString _nodeCaption;

};

#endif // AICCTOOLBUTTON_H
