#ifndef TREE_VIEW_READONLY_DELEGATE_H
#define TREE_VIEW_READONLY_DELEGATE_H

#include <QItemDelegate>

///只读代理，用于tableWidget或treeWidget设置列只读
class ReadOnlyDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    ReadOnlyDelegate(QObject *parent = nullptr):QItemDelegate(parent){}
    QWidget *createEditor(QWidget* parent,const QStyleOptionViewItem &option,const QModelIndex &index)const{return nullptr;}
};

#endif // TREE_VIEW_READONLY_DELEGATE_H
