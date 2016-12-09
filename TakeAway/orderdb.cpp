#include "orderdb.h"

OrderDB::OrderDB()
{}

void OrderDB::updateOrderState(int oid)
{
    if(!connDB())
    {
        return;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare(
                QString("update Order_State set O_state=1 where O_id='%1';").arg(oid)
                );
    updateQuery.exec();

    updateQuery.clear();
    disconnDB();
    return;
}

OrderDS OrderDB::searchRecentOrder(QSharedPointer<UserDS> &user)
{
    OrderDS orderds;
    if(!connDB())
    {
        return orderds;
    }

    QSqlQuery myQuery;
    QSqlQuery menuQuery;
    QSqlQuery orderQuery;
    QMap<int, int> menu;

    myQuery.prepare(
            QString("Select Order_State.O_id from Order_State where  Order_State.O_state=0 and Order_State.B_id='%1';").arg(user->getUid())
            );
    if(!myQuery.exec())
    {
        return orderds;
    }
    myQuery.last();
    int oid = myQuery.value(0).toInt();

    orderds.oid = oid;
    menuQuery.prepare(
             QString("Select M_id,quantity from Order_Menu where Order_Menu.O_id='%1';").arg(oid)
             );
    menuQuery.exec();
    while(menuQuery.next())
    {
        menu.insert(menuQuery.value(0).toInt(), menuQuery.value(1).toInt());
    }
    QMap<int, int>::iterator iter = menu.begin();
    for(int i = 0; i < menu.size(); i++, iter++)
    {
        orderQuery.prepare(
              QString("Select M_name from Menu where M_id='%1';").arg(iter.key())
              );
        orderQuery.exec();
        orderQuery.next();
        orderds.order.insert(orderQuery.value(0).toString(), iter.value());
    }

    menuQuery.clear();
    orderQuery.clear();
    myQuery.clear();
    disconnDB();
    return orderds;
}

QString OrderDB::getTime(int oid)
{
    QString time;
    if(!connDB())
    {
        return time;
    }

    QSqlQuery timeQuery;
    timeQuery.prepare(
                QString("select O_time from Order_Info where O_id='%1';").arg(oid)
                );
    timeQuery.exec();
    timeQuery.next();

    time = timeQuery.value(0).toString();
    timeQuery.clear();
    disconnDB();
    return time;
}
