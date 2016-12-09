#include "sorderdb.h"

SOrderDB::SOrderDB()
{

}

std::map<std::vector<std::string>, std::string> SOrderDB::getOrder(int sid)
{
    std::map<std::vector<std::string>, std::string> order;
    order.clear();
    if(!connDB())
    {
        return order;
    }

    QSqlQuery orderQuery;
    orderQuery.prepare(
            QString("select O_id,B_id from Order_State where O_state=0 and O_id in (SELECT O_id FROM Order_Info WHERE S_id = '%1');").arg(sid)
            );
    if(!orderQuery.exec())
    {
        return order;
    }

    while(orderQuery.next())
    {
        int oid = orderQuery.value(0).toInt();
        int bid = orderQuery.value(1).toInt();
        QSqlQuery userQuery;
        userQuery.prepare(
                QString("select B_name,B_tel from Buyer where B_id='%1';").arg(bid)
                );
        userQuery.exec();
        userQuery.next();
        QString str1 = userQuery.value(0).toString()+ "\t\t电话:" + userQuery.value(1).toString();
        userQuery.clear();

        QSqlQuery menuQuery;
        menuQuery.prepare(
                QString("select Order_Menu.quantity, Menu.M_name from Order_Menu, Menu where Order_Menu.O_id='%1' and Order_Menu.M_id=Menu.M_id;").arg(oid)
                );
        menuQuery.exec();
        std::vector<std::string> vec;
        vec.clear();
        while(menuQuery.next())
        {
            QString str2 = menuQuery.value(1).toString() + "\t*" + menuQuery.value(0).toString();
            vec.push_back(str2.toStdString());
        }
        menuQuery.clear();

        order.insert(std::pair<std::vector<std::string>, std::string>(vec, str1.toStdString()));
    }

    orderQuery.clear();
    disconnDB();
    return order;
}
