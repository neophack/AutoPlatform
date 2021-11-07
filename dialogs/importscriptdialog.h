#ifndef IMPORTSCRIPTDIALOG_H
#define IMPORTSCRIPTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QStringList>
#include <QSharedPointer>

#include "nodeparser/invocable.hpp"
#include "nodeparser/invocable_parser.hpp"
#include "nodeparser/module_library.hpp"

namespace Ui {
class ImportScriptDialog;
}

class ImportScriptDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportScriptDialog(QWidget *parent = nullptr);
    ~ImportScriptDialog();
    void setImportProcess(const int cvalue,const int mvalue);
    void setListModels(ModuleLibrary *moduleLibrary);

Q_SIGNALS:
    void filesSelected(const QStringList files);

private:
    void initButton();
private:
    Ui::ImportScriptDialog *ui;
};

#endif // IMPORTSCRIPTDIALOG_H
