#ifndef AICCBREADCRUMBNAVIGATION_H
#define AICCBREADCRUMBNAVIGATION_H

#include <QLabel>
#include <QDebug>
#include <QStandardItemModel>

class AICCBreadcrumbNavigation : public QLabel
{
    Q_OBJECT
public:
    AICCBreadcrumbNavigation(QWidget *parent=nullptr){
        //面包屑导航显示信息原始参考数据
        //        QString str_navigation = QString("<style>a{text-decoration:none;font-size:15px;color:black;vertical-align:middle} img{vertical-align:bottom}</style><img src=':/res/breadcrumbNavigation/model_16.png'/><a href='level1' >level1</a><img src=':/res/breadcrumbNavigation/rightArrow_16.png'  />&nbsp;&nbsp;<img src=':/res/breadcrumbNavigation/subsystem_16.png'/><a href='level2'>level2</a><img src=':/res/breadcrumbNavigation/rightArrow_16.png'/>&nbsp;");

        QStringList list ;
        list << "root" << "level2" << "level3" << "level3" << "level4";
        this->makeNavigationData(list);
        this->refreshNavigationView();
    };
    ~AICCBreadcrumbNavigation(){

    }

public:
    ///根据录入的字符串列表，生成QStandardModel数据
    void makeNavigationData(const QStringList ndatas)
    {
        QStandardItem *aitem;
        QStringListIterator sliterator(ndatas);
        int i=0;
        while(sliterator.hasNext()){
            aitem = new QStandardItem();
            QVariant qv(sliterator.next());
            aitem->setData(qv);
            _model.setItem(0,i,aitem);
            i++;
        }

    }

    ///刷新面包屑导航显示
    void refreshNavigationView(){
        if(_model.columnCount()==0) return;
        QString labelRichText = "<style>a{text-decoration:none;font-size:15px;color:black;vertical-align:top} img{vertical-align:top}</style>";
        for(int i=0;i<_model.columnCount();i++){
            QStandardItem *item = _model.item(0,i);
            QString itemName = item->data().toString();
            labelRichText += i==0?"<img src=':/res/breadcrumbNavigation/model_16.png'/>":"<img src=':/res/breadcrumbNavigation/subsystem_16.png'  />&nbsp;&nbsp;";
            labelRichText += "<a href='"+itemName+"' >"+itemName+"</a><img src=':/res/breadcrumbNavigation/rightArrow_16.png'  />&nbsp;&nbsp;";
        }
        this->setText(labelRichText);
        connect(this,&QLabel::linkActivated,this,[&](const QString &link){
// TODO 此处需要改造，点击链接后根据点击的信息不同，打开不同的子系统窗口
            qDebug() << "clicked link:" << link << endl;
        });
    }
private:
    QStandardItemModel _model;
};

#endif // AICCBREADCRUMBNAVIGATION_H
