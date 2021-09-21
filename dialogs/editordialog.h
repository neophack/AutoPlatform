#ifndef EDITORDIALOG_H
#define EDITORDIALOG_H

#include <QDialog>

namespace Ui {
class EditorDialog;
}

class EditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditorDialog(QWidget *parent = nullptr);
    ~EditorDialog();

private:
    Ui::EditorDialog *ui;
};

#endif // EDITORDIALOG_H
