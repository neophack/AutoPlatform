#ifndef AICCSQLITE_H
#define AICCSQLITE_H

#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>


class AICCSqlite
{
//    Q_OBJECT
public:
    AICCSqlite(){

    }
    ///初始化数据库链接
    void initDatabaseConnection(){

        QSqlDatabase sqlDatabase;
        _database = sqlDatabase.addDatabase("QSQLITE");
        _database.setDatabaseName(QApplication::applicationDirPath()+"/sqlite/node.db3");
        if(!_database.open()){
//            QMessageBox::warning(0,QObject::tr("Database Error"),database.lastError());
            qDebug() <<  _database.lastError();
            return ;
        }
    }

    ///sql语句执行
//    template <typename F>
    QSqlQuery query(const QString sql){
        if(_sqlQuery.exec(sql)){
            return _sqlQuery;
        }else{
            qDebug() << _sqlQuery.lastError();
        }
    }

    ///关闭数据库连接
    void closeConnection(){
        _database.close();
    }
private:
    QSqlDatabase _database;
    QSqlQuery _sqlQuery;
};

#endif // AICCSQLITE_H
