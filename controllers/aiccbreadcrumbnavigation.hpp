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

        //    ui->l_breadcrumb_navigation->setText(str_navigation);

        QStringList list ;
//        list << "root";
//        list << "root" << "level2" << "level3" << "level3" << "level4";
        this->makeNavigationData(list);
        this->refreshNavigationView();
    };
    ~AICCBreadcrumbNavigation(){

    }

public:
    ///根据url,改变导航条数据
    void makeNavigationData(const QString &url){
        QStringList lpath = url.split("/");
        lpath.removeAll("");
        makeNavigationData(lpath);
    }

    ///根据录入的字符串列表，生成QStandardModel数据
    void makeNavigationData(const QStringList ndatas){
        QStandardItem *aitem;
        QStringListIterator sliterator(ndatas);
        _model.clear();
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
            labelRichText += i==0?"<img src=':/res/breadcrumbNavigation/model_16.png'/>":"<img src=':/res/breadcrumbNavigation/subsystem_16.png' />&nbsp;&nbsp;";
            QString link;
            for(int j=0;j<=i;j++){
                link += "/"+_model.item(0,j)->data().toString();
            }
            labelRichText += "<a href='"+link+"' >"+itemName+"</a><img src=':/res/breadcrumbNavigation/rightArrow_16.png'  />&nbsp;&nbsp;";
        }
        this->setText(labelRichText);
    }
private:
    QStandardItemModel _model;
};

#endif // AICCBREADCRUMBNAVIGATION_H
