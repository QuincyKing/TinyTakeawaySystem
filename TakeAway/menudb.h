#ifndef MENUDB
#define MENUDB

#include "prerequisite.h"
#include "userds.h"
#include "abstractdb.h"

class MenuDB : public AbstractDB
{
  public:
    MenuDB();

    void setShop(int shop);
    int  getShop();
    QMap<QString, int> searchShopMenu();
    void submitOrder(QMap<int, int> &, QSharedPointer<UserDS> &, int, int);
  private:
    int shop;
};
#endif // MENUDB

