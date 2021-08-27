#ifndef QTGUIDRAG_H
#define QTGUIDRAG_H

#include <QWidget>
#include "ui_mainwindow.h"

class QtGuiDrag:public QWidget {
    Q_OBJECT
public:
    QtGuiDrag(QWidget *parent = Q_NULLPTR):QWidget(parent){
//        ui.setupUi(this);
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setAttribute(Qt::WA_TranslucentBackground,true);
    }
    ~QtGuiDrag(){}
    void setShowText(QString text){
//        ui.label->setText(text);
    }

private :
    Ui::MainWindow ui;
};

#endif // QTGUIDRAG_H
