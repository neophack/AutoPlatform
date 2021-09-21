#ifndef PROJECTDIALOG_H
#define PROJECTDIALOG_H

#include <QDialog>
#include <iostream>
#include <QFile>

namespace Ui {
class ProjectDialog;
}

using namespace std;

class ProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectDialog(QWidget *parent = nullptr);
    ~ProjectDialog();

private:
    void initButton();
    void initOpenPath();
    void initStackedFirst();
    void initStackedSecond();
    void writeProjectXml(QFile &file);

private:
    Ui::ProjectDialog *ui;
    QString projectName;
    QString projectPath;
    QString config1;
    QString config2;

};

#endif // PROJECTDIALOG_H
