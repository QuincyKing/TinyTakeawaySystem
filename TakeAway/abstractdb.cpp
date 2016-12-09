#include "abstractdb.h"

AbstractDB::AbstractDB()
{

}

bool AbstractDB::connDB()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(QString("DRIVER={SQL SERVER};"
                                   "SERVER=%1;"
                                   "DATABASE=%2;"
                                   "UID=%3;"
                                   "PWD=%4;").arg("127.0.0.1,1433")
                           .arg("TakeAway")
                           .arg("sa")
                           .arg("13396731991"));
    if (!db.open())
    {
        QSqlDatabase::removeDatabase("QODBC");
        QMessageBox msgBox;
        msgBox.setText(db.lastError().text());
        msgBox.exec();
        return false;
    }
    else
    {
        qDebug()<<"connect to database success";
    }
    return true;
}

void AbstractDB::disconnDB()
{
    if(db.isOpen())
    {
        db.close();
    }
    QSqlDatabase::removeDatabase("QODBC");
}

