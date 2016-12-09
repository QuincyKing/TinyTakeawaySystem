#ifndef SMENUDB
#define SMENUDB

#include "prerequisite.h"
#include <map>
#include <string>
#include "abstractdb.h"

class SMenuDB : public AbstractDB
{
public:
    SMenuDB();

    QMap<QString, int> getMenu(int sid);
    void upgradeMenu(QMap<QString, int> &menu, int);
};
#endif // SMENUDB

