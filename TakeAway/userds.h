#ifndef USERDS_H
#define USERDS_H

#include "prerequisite.h"

class UserDS
{
public:
    enum userDataType {
        Invalid,
        Valid,
        ErrOpenDB,
        ErrSqlExec,
        ErrNoData,
        ErrMultiData,
        ErrExistData
    };

    UserDS();
    UserDS(userDataType userType);
    UserDS(QString username, QString password);
    UserDS(QString username, QString password, bool userFlag);
    UserDS(int uid, QString username, QString password, bool userFlag, QString tele, int money);
    UserDS(int uid, QString username, QString password, bool userFlag, QString tele, int money, QString sellername);
    UserDS(int uid, QString username, QString password, bool userFlag, QString tele, int money, userDataType userType);

    void setUserType(userDataType userType);
    void setUsername(QString username);
    void setPassword(QString password);
    void setTele(QString tele);
    void setUserFlag(bool userFlag);
    void setSellername(QString sellername);
    void setUid(int uid);
    void setMoney(int money);

    userDataType getUserType();
    QString getUsername();
    QString getPassword();
    QString getTele();
    bool getUserFlag();
    QString getSellername();
    int getUid();
    int getMoney();

    void update(UserDS &user);
    void update(QString username, QString password, bool userFlag, QString tele, int money);
    void update(int uid, QString username, QString password, bool userFlag, QString tele, int money);
    void update(QString username, QString password, bool userFlag, QString tele, int money, QString sellername);
    void update(int uid, QString username, QString password, bool userFlag, QString tele, int money, QString sellername);
    void update(int uid, QString username, QString password, bool userFlag, QString tele, int money, userDataType userType);

    void clear();

    bool isValidUsernamePattern();
    bool isValidPasswordPattern();
    bool isValidTelePattern();

    bool isValidUsernamePattern(QString username);
    bool isValidPasswordPattern(QString password);
    bool isValidTelePattern(QString tele);

    QString userDataTypeStr(userDataType);

private:
    userDataType userType;
    bool userFlag;
    QString username;
    QString password;
    QString tele;
    QString sellername;
    int money;
    int uid;
};

#endif // USERDS_H
