#include "sellerdb.h"

SellerDB::SellerDB()
{}

QMap<int, QString> SellerDB::searchAllShop()
{
    QMap<int, QString> shop;
    if(!connDB())
    {
        return shop;
    }
    QSqlQuery myQuery;
    myQuery.prepare(
            QString("SELECT S_id,S_shopname FROM Seller;")
            );
    if(!myQuery.exec())
    {
        return shop;
    }
    while(myQuery.next())
    {
        shop.insert( myQuery.value(0).toInt(), myQuery.value(1).toString() );
    }

    myQuery.clear();
    disconnDB();

    return shop;
}

QString SellerDB::searchShopName(int shop)
{
    QString shopName;

    if(!connDB())
    {
        return "";
    }
    QSqlQuery myQuery;
    myQuery.prepare(
            QString("SELECT S_shopname FROM Seller WHERE S_id = %1;").arg(shop)
            );
    if(!myQuery.exec())
    {
        return "";
    }
    while(myQuery.next())
    {
        shopName = myQuery.value(0).toString();
    }

    myQuery.clear();
    disconnDB();

    return shopName;
}

