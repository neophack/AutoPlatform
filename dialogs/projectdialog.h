#ifndef PROJECTDIALOG_H
#define PROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class ProjectDialog;
}

class ProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectDialog(QWidget *parent = nullptr);
    ~ProjectDialog();

private:
    void initButton();
    void initOpenPath();

private:
    Ui::ProjectDialog *ui;
};

#endif // PROJECTDIALOG_H
