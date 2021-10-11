#ifndef NODEPARAMETERSDIALOG_H
#define NODEPARAMETERSDIALOG_H

#include <QDialog>
#include <QTableWidget>

#include "itemreadonlydelegate.h"

namespace Ui {
class NodeParametersDialog;
}

class NodeParametersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NodeParametersDialog(QWidget *parent = nullptr);
    ~NodeParametersDialog();

    QTableWidget *getTableNodeParameters();

private:
    Ui::NodeParametersDialog *ui;
//    QTableWidget *_tableWidget;
};

#endif // NODEPARAMETERSDIALOG_H
