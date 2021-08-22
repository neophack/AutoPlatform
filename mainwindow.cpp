#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->InitTreeView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitTreeView()
{
    QStandardItemModel* model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("序号")<<QStringLiteral(""));
    for(int i=0;i<5;i++){
        QList<QStandardItem*> items1;
        QStandardItem* item1 = new QStandardItem(QIcon(":/image/res/ticon1.png"),QString::number(i));
        QStandardItem* item2 = new QStandardItem( QStringLiteral("一级节点"));

        items1.append(item1);
        items1.append(item2);
        model->appendRow(items1);

        for(int j=0;j<5;j++)
        {
            QList<QStandardItem*> items2;
            QStandardItem* item3 = new QStandardItem(QString::number(j));
            QStandardItem* item4 = new QStandardItem(QStringLiteral("二级节点"));
            items2.append(item3);
            items2.append(item4);
            item1->appendRow(items2);

            for(int k=0;k<5;k++)
            {
                QList<QStandardItem*> items3;
                QStandardItem* item5 = new QStandardItem(QString::number(k));
                QStandardItem* item6 = new QStandardItem(QStringLiteral("三级节点"));
                items3.append(item5);
                items3.append(item6);
                item3->appendRow(items3);
            }
        }
    }

    ui->treeView->setModel(model);
}
