#ifndef SORDERDB_H
#define SORDERDB_H

#include "prerequisite.h"
#include "abstractdb.h"

class SOrderDB : public AbstractDB
{
public:
    SOrderDB();
    std::map<std::vector<std::string>, std::string> getOrder(int sid);
};

#endif // SORDERDB_H
