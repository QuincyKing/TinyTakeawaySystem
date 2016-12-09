#ifndef ABSTRACTDB_H
#define ABSTRACTDB_H

#include "prerequisite.h"

class AbstractDB
{
public:
    AbstractDB();

    bool connDB();
    void disconnDB();

protected:
    QSqlDatabase db;
};

#endif // ABSTRACTDB_H
