#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QString>
#include "aicctreewidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
//    void startDrag(Qt::DropActions supportedActions);
//    void dragMoveEvent(QDragMoveEvent *e);

private:
    Ui::MainWindow *ui;
    void createMenu();
    void initTreeView();
    void initNodeEditor();
    void initSplitter();
    void initTableWidget();
    void setTreeNode(QTreeWidget *tw,const char* ptext,const char* picon);
};
#endif // MAINWINDOW_H
