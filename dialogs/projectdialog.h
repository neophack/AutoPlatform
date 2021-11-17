#ifndef PROJECTDIALOG_H
#define PROJECTDIALOG_H

#include <QDialog>
#include <iostream>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QtXml/QDomDocument>
#include <cmath>

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

    const QString &getProjectName() const;
    const QString &getProjectPath() const;
    const QStringList &getFlowSceneSaveFiles() const;
    void readProjectXml(QFile &file);
    void setProjectPath(const QString &newProjectPath);

Q_SIGNALS:
    void projectCreateCompleted(bool success);


private:
    void initButton();
    void initOpenPath();
    void initStackedFirst();
    void initStackedSecond();
    void writeProjectXml(QFile &file);

private:
    Ui::ProjectDialog *ui;
    QString projectName;
    //项目路径保存到项目名的上一层，/home/fc/works/AutoCar
    QString projectPath;
    QString config1;
    QString config2;
    QStringList flowSceneSaveFiles;

};

#endif // PROJECTDIALOG_H
