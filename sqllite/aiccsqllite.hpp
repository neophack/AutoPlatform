#ifndef AICCSQLLITE_H
#define AICCSQLLITE_H

#include <qt5/QtSql/QSqlDatabase>
#include <qt5/QtSql/QSql>
#include <QApplication>


class AICCSqlLite
{
//    Q_OBJECT
public:
    AICCSqlLite(){
        QSqlDatabase database = QSqlDatabase
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName(QApplication::applicationDirPath()+"/sqlite.db");
        if(!database.open()){
            QMessageBox::warning(0,QObject::tr("Database Error"),database.lastError().text());
            return false;
        }
    }
};

#endif // AICCSQLLITE_H
