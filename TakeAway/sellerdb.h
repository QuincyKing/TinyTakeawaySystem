#ifndef SELLERDB
#define SELLERDB

#include "prerequisite.h"
#include "abstractdb.h"

class SellerDB : public AbstractDB
{
public:
    SellerDB();

    QMap<int, QString> searchAllShop();
    QString searchShopName(int shop);
};

#endif // SELLERDB

