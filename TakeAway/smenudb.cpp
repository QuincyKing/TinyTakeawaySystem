#include "smenudb.h"

SMenuDB::SMenuDB()
{}

QMap<QString, int> SMenuDB::getMenu(int sid)
{
    QMap<QString, int> menu;
    if(!connDB())
    {
        return menu;
    }

    QSqlQuery menuQuery;
    menuQuery.prepare(
            QString("SELECT M_id,M_name,M_price FROM Menu WHERE S_id = %1;").arg(sid)
            );
    if(!menuQuery.exec())
    {
        return menu;
    }

    while(menuQuery.next())
    {
        int id = menuQuery.value(0).toInt();
        QString name = QString::number(id) + ":" + menuQuery.value(1).toString();
        int price = menuQuery.value(2).toInt();
        menu.insert( name, price );
    }

    menuQuery.clear();
    disconnDB();
    return menu;
}

void SMenuDB::upgradeMenu(QMap<QString, int> &menu, int sid)
{
    if(!connDB())
    {
        return;
    }
    QMap<QString, int>::iterator cursor = menu.begin();

    for(; cursor != menu.end(); cursor++)
    {
        QString str = cursor.key();
        QString name = str.split(":").at(0);

        int id = str.split(":").at(1).toInt();
        QSqlQuery menuQuery;
        if(id != 0)
        {
        menuQuery.prepare(
                QString("update Menu set M_name='%2',M_price='%3' where M_id='%1';").arg(id).arg(name).arg(cursor.value())
                );
        menuQuery.exec();
        }
        else
        {
            menuQuery.prepare(
                    QString("insert into Menu(S_id, M_name, M_price) values('%1', '%2', '%3');").arg(sid).arg(name).arg(cursor.value())
                    );
            menuQuery.exec();
        }
        menuQuery.clear();
    }

    disconnDB();
    return;
}


