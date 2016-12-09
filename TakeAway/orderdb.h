#ifndef ORDERDB
#define ORDERDB

#include "prerequisite.h"
#include "userds.h"
#include "orderds.h"
#include "abstractdb.h"


class OrderDB : public AbstractDB
{
public:
    OrderDB();
    OrderDS searchRecentOrder(QSharedPointer<UserDS> &user);
    void updateOrderState(int oid);
    QString getTime(int oid);

};
#endif // ORDERDB

