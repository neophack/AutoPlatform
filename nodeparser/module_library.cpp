//
// Created by 刘典 on 2021/9/12.
//

#include "module_library.hpp"
#include "invocable_parser.hpp"
#include <algorithm>
#include <QtDebug>
namespace fs = std::filesystem;

void ModuleLibrary::importFiles(const QStringList &files) {
//    std::list<Invocable> parse_result;
    InvocableParser parser;
    parser.setIncludePaths(_includePaths);
    _parseResult.clear();
//    for(const auto & file: files) {
    for(int i=0;i<files.count();i++){
        const auto &file = files[i];
        fs::path p = file.toStdString();
        if(!fileInIncludePaths(p)) {
            emit errorOccured(QString("文件 '%1' 不在 Include Paths 中").arg(file));
            continue;
        }
        std::string error_message;
        if(!parser.parse(p, _parseResult, error_message)) {
            emit errorOccured(QString("解析文件 '%1' 时发生错误: %2").arg(file, QString::fromStdString(error_message)));
        } else {
            qDebug() << "result size: " << _parseResult.size();
            setInvocables(_parseResult);
        }
        QStringList fileSplitPath = file.split("/");
        emit fileParserCompleted(files.count(),i,fileSplitPath[fileSplitPath.count()-1]);
    }
}

bool ModuleLibrary::fileInIncludePaths(const std::filesystem::path & file) {
    return std::search(file.begin(), file.end(), _includePaths.begin(), _includePaths.end()) == file.begin();

}

int ModuleLibrary::rowCount(const QModelIndex &parent) const {
    return _invocableList.size();
}

QVariant ModuleLibrary::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return {};

    if (index.row() >= _invocableList.size())
        return {};

    if (role == Qt::DisplayRole)
        return QString::fromStdString(_invocableList.at(index.row()).getName());
    else
        return {};
}

void ModuleLibrary::setInvocables(const std::list<Invocable> &list) {
    beginResetModel();
    _invocableList.clear();
    std::copy(list.begin(), list.end(), std::back_inserter(_invocableList));
    endResetModel();
    emit importCompleted();
}

