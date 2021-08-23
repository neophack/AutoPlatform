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
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("资源"));
        QList<QStandardItem*> items_first;
//        QStandardItem* item_device,item_ecu,item_drive,item_algorithm,item_signal,item_IO;
        QStandardItem* item_device = new QStandardItem(QIcon(":/image/res/ticon1.png"),QStringLiteral("设备"));
        QStandardItem* item_ecu = new QStandardItem(QIcon(":/image/res/ticon1.png"),QStringLiteral("ECU"));
        QStandardItem* item_drive = new QStandardItem(QIcon(":/image/res/ticon1.png"),QStringLiteral("驱动"));
        QStandardItem* item_algorithm = new QStandardItem(QIcon(":/image/res/ticon1.png"),QStringLiteral("算法"));
        QStandardItem* item_signal = new QStandardItem(QIcon(":/image/res/ticon1.png"),QStringLiteral("信号"));
        QStandardItem* item_IO = new QStandardItem(QIcon(":/image/res/ticon1.png"),QStringLiteral("IO"));

        items_first.append(item_device);
                items_first.append(item_ecu);
                items_first.append(item_drive);
                items_first.append(item_algorithm);
                items_first.append(item_signal);
                        items_first.append(item_IO);

//        for()

        model->appendRow(item_device);
        model->appendRow(item_ecu);
        model->appendRow(item_drive);
        model->appendRow(item_algorithm);
        model->appendRow(item_signal);
        model->appendRow(item_IO);

//        for(int i=0;i<model->rowCount();i++)
//            model->

//        for(int j=0;j<5;j++)
//        {
//            QList<QStandardItem*> items2;
//            QStandardItem* item3 = new QStandardItem(QString::number(j));
//            QStandardItem* item4 = new QStandardItem(QStringLiteral("二级节点"));
//            items2.append(item3);
//            items2.append(item4);
//            item1->appendRow(items2);

//            for(int k=0;k<5;k++)
//            {
//                QList<QStandardItem*> items3;
//                QStandardItem* item5 = new QStandardItem(QString::number(k));
//                QStandardItem* item6 = new QStandardItem(QStringLiteral("三级节点"));
//                items3.append(item5);
//                items3.append(item6);
//                item3->appendRow(items3);
//            }
//        }
//    }

    ui->treeView->setModel(model);
}
