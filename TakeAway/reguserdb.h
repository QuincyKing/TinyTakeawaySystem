#ifndef REGUSERDB_H
#define REGUSERDB_H

#include "prerequisite.h"
#include "userds.h"
#include "abstractdb.h"

class RegUserDB : public AbstractDB
{
public:
    RegUserDB();

    bool searchUserByUsername(UserDS& user);
    bool addUser(UserDS& user);
    bool authUser(UserDS& user);
    bool searchUserByUsernameAndPassword(UserDS& user);
};

#endif // REGUSERDB_H
