//
// Created by 刘典 on 2021/9/12.
//

#ifndef NODEDRIVING_MODULE_LIBRARY_HPP
#define NODEDRIVING_MODULE_LIBRARY_HPP
#include <QStringList>
#include <QApplication>
#include <QString>
#include <filesystem>
#include <list>
#include <vector>
#include <QAbstractListModel>
#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/NodeStyle>
#include <nodes/FlowViewStyle>
#include <nodes/ConnectionStyle>
#include "invocable.hpp"
#include "models.hpp"
#include <iostream>
class ModuleLibrary: public QAbstractListModel {
    Q_OBJECT
public Q_SLOTS:
    void importFiles(const QStringList &files);
Q_SIGNALS:
    void errorOccured(const QString &error_message);
    void importCompleted();
    void fileParserCompleted(const int count,const int index,const QString filename);

private:
    std::filesystem::path _includePaths{(QApplication::applicationDirPath()+"/nodeconfig").toStdString()};
    std::vector<Invocable> _invocableList;
    std::list<Invocable> _parseResult;
    bool fileInIncludePaths(const std::filesystem::path & file);
    void setInvocables(const std::list<Invocable> & list);

public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    std::shared_ptr<QtNodes::DataModelRegistry> test2() {
        auto ret = std::make_shared<QtNodes::DataModelRegistry>();
            for(const auto & inv: _invocableList) {
                auto f = [inv](){return std::make_unique<InvocableDataModel>(inv);};
                ret->registerModel<InvocableDataModel>(f, "test");

            }
        return ret;
    }

    std::list<Invocable> getParseResult(){return _parseResult;}

};


#endif //NODEDRIVING_MODULE_LIBRARY_HPP
