#ifndef NODETREEDIALOG_H
#define NODETREEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QToolButton>
#include <QSharedPointer>
#include <QString>
#include <iostream>
#include <list>
#include <vector>
#include <filesystem>
#include <algorithm>
#include "stdio.h"

#include <nodes/DataModelRegistry>

#include <nodeparser/invocable.hpp>
#include <nodeparser/invocable_parser.hpp>
#include <nodeparser/models.hpp>
#include <nodeparser/module_library.hpp>

using QtNodes::DataModelRegistry;

namespace Ui {
class NodeTreeDialog;
}

class NodeTreeDialog : public QDialog
{
    Q_OBJECT

public:
    using CategoriesSet = std::set<QString>;

    explicit NodeTreeDialog(QWidget *parent = nullptr);
    ~NodeTreeDialog();
//    void setDataModelRegistry(DataModelRegistry *pdmr);
    void setDataModelRegistry(std::shared_ptr<DataModelRegistry> pdmr);

Q_SIGNALS:
    void filesSelected(const QStringList &selected);

private:
    void initTreeWidget();
    void initNodeConfig();

private:
    Ui::NodeTreeDialog *ui;
    std::shared_ptr<DataModelRegistry> _dataModelRegistry;

};

#endif // NODETREEDIALOG_H
