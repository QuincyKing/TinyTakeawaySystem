#include "menudb.h"
#include "reguserdb.h"

MenuDB::MenuDB()
{}

void MenuDB::setShop(int shop)
{
    this->shop = shop;
}

int  MenuDB::getShop()
{
    return shop;
}

QMap<QString, int> MenuDB::searchShopMenu()
{
    QMap<QString, int> map;
    if(!connDB())
    {
        return map;
    }
    QSqlQuery myQuery;
    myQuery.prepare(
            QString("SELECT M_id,M_name,M_price FROM Menu WHERE S_id = %1;").arg(shop)
            );
    if(!myQuery.exec())
    {
        return map;
    }
    while(myQuery.next())
    {
        QString tmp = myQuery.value(1).toString() + "\n price:" + myQuery.value(2).toString();
        map.insert(tmp, myQuery.value(0).toInt());
    }

    myQuery.clear();
    disconnDB();

    return map;
}

void MenuDB::submitOrder(QMap<int, int> &order, QSharedPointer<UserDS>& user, int shop, int totalprice)
{
    if(!connDB())
    {
        return;
    }

    QSqlQuery orderQuery;
    QDateTime current_date_time = QDateTime::currentDateTime();
    current_date_time = current_date_time.addSecs(2400);
    QString time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    orderQuery.prepare(
                QString("INSERT INTO Order_Info ( B_id, S_id, O_time) VALUES (:bid, :sid, :time);")
            );
    orderQuery.bindValue(":bid", user->getUid());
    orderQuery.bindValue(":sid", shop);
    orderQuery.bindValue(":time", time);

    if(!orderQuery.exec())
    {
        QMessageBox msgBox;
        msgBox.setText("3!");
        msgBox.exec();
        return;
    }

    QSqlQuery myQuery;
    myQuery.prepare(
                QString("select * from Order_Info")
                );
    myQuery.exec();
    myQuery.last();
    int oid = myQuery.value(0).toInt();

    QSqlQuery stateQuery;
    stateQuery.prepare(
                  QString("INSERT INTO Order_State(O_id, B_id, O_state) VALUES(:oid, :bid, :state);")
                  );
    stateQuery.bindValue(":oid", oid);
    stateQuery.bindValue(":bid", user->getUid());
    stateQuery.bindValue(":state", 0);

     if(!stateQuery.exec())
     {
         QMessageBox msgBox;
         msgBox.setText("2!");
         msgBox.exec();
         return;
     }

    QMap<int, int>::iterator iter = order.begin();
    for(int i = 0; i < order.size(); i++, iter++)
    {
         QSqlQuery menuQuery;
         menuQuery.prepare(
            QString("insert into Order_Menu (O_id, M_id, quantity) values (:oid, :mid, :qua);")
            );
        menuQuery.bindValue(":oid", oid);
        menuQuery.bindValue(":mid", iter.key());
        menuQuery.bindValue(":qua", iter.value());

        if(!menuQuery.exec())
        {
            QMessageBox msgBox;
            msgBox.setText("1!");
            msgBox.exec();
            return;
        }
        menuQuery.clear();
    }

    QSqlQuery userQuery;

    userQuery.prepare(
           QString("update Buyer set B_money='%1' where B_id='%2';")
                  .arg(user->getMoney()).arg(user->getUid())
            );

    userQuery.prepare(
            QString("update Seller set S_money=S_money+'%1' where S_id='%2';")
                    .arg(totalprice).arg(shop)
            );


    if(!userQuery.exec())
    {
        QMessageBox msgBox;
        msgBox.setText("Error!");
        msgBox.exec();
        return;
    }

    stateQuery.clear();
    orderQuery.clear();
    myQuery.clear();
    userQuery.clear();
    disconnDB();
    return;
}
