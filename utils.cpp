#include "utils.h"

 QStringList getFlieList(const QString &path){
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.hpp";
//    QStringList files = dir.entryList(nameFilters,QDir::Files|QDir::Readable,QDir::Name);
//    QFileInfoList filist =  dir.entryInfoList(nameFilters,QDir::Readable,QDir::Name);
    QFileInfoList filist = dir.entryInfoList(nameFilters);
    QStringList files;
    for(QFileInfo fileInfo:filist)
        files << fileInfo.absoluteFilePath();


    return files;
}
