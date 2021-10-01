#ifndef AICCMODEL_H
#define AICCMODEL_H

#include <QStandardItemModel>
#include <QMimeData>
#include <QTreeWidget>

class TreeNode
{
public:
    TreeNode(const QString&text = ""):mText(text){}
    ~TreeNode(){}
    QString mText;
    TreeNode* mParentNode;                                  //父节点
    QList<TreeNode*> mChildNodes;                   //子节点
};


class AICCModel:public QStandardItemModel{
public:
    AICCModel(){};
    AICCModel(QTreeWidget* treeWidget):QStandardItemModel(treeWidget){};
protected:
    Qt::ItemFlags flags(const QModelIndex &index) const
    {
        Qt::ItemFlags flags = QAbstractItemModel::flags(index);
        flags = flags | Qt::ItemIsDragEnabled;
        return flags;
    }

    QMimeData *mimeData(const QModelIndexList &indexes) const
    {
        QMimeData* mimeD = QAbstractItemModel::mimeData(indexes);
        if(indexes.size() >0)
        {
            QModelIndex index = indexes.at(0);
            AICCModel* node = (AICCModel*)index.internalPointer();
            QByteArray encoded;
            QDataStream stream(&encoded, QIODevice::WriteOnly);
            stream << (qint64)(node);
            mimeD->setData("Node/NodePtr",encoded);
        }
        else
            mimeD->setData("Node/NodePtr","NULL");

        return mimeD;
    }

public:
    TreeNode* mRootNode;
};

#endif // AICCMODEL_H
