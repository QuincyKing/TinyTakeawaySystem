#include "userds.h"

UserDS::UserDS()
{
    userType = Invalid;
}

UserDS::UserDS(userDataType userType)
{
    this->userType = userType;
}

UserDS::UserDS(QString username, QString password)
{
    this->username = username;
    this->password = password;
}

UserDS::UserDS(QString username, QString password, bool userFlag)
{
    this->username = username;
    this->password = password;
    this->userFlag = userFlag;
}

UserDS::UserDS(int uid, QString username, QString password, bool userFlag, QString tele, int money)
{
    this->username = username;
    this->password = password;
    this->userFlag = userFlag;
    this->tele = tele;
    this->uid  = uid;
    this->money = money;
}

UserDS::UserDS(int uid, QString username, QString password, bool userFlag, QString tele, int money, QString sellername)
{
    this->username = username;
    this->password = password;
    this->userFlag = userFlag;
    this->tele = tele;
    this->sellername = sellername;
    this->uid = uid;
    this->money = money;
}

UserDS::UserDS(int uid, QString username, QString password, bool userFlag, QString tele, int money, userDataType userType)
{
    this->username = username;
    this->password = password;
    this->userFlag = userFlag;
    this->tele = tele;
    this->userType = userType;
    this->uid = uid;
    this->money = money;
}

void UserDS::setUserType(userDataType userType)
{
    this->userType = userType;
}

void UserDS::setUsername(QString username)
{
    this->username = username;
}

void UserDS::setPassword(QString password)
{
    this->password = password;
}

void UserDS::setTele(QString tele)
{
    this->tele = tele;
}

void UserDS::setUserFlag(bool userFlag)
{
    this->userFlag = userFlag;
}

void UserDS::setSellername(QString sellername)
{
    this->sellername = sellername;
}

void UserDS::setUid(int uid)
{
    this->uid= uid;
}

void UserDS::setMoney(int money)
{
    this->money = money;
}

UserDS::userDataType UserDS::getUserType()
{
    return userType;
}

QString UserDS::getUsername()
{
    return username;
}

QString UserDS::getPassword()
{
    return password;
}

bool UserDS::getUserFlag()
{
    return userFlag;
}

QString UserDS::getTele()
{
    return tele;
}

QString UserDS::getSellername()
{
    return sellername;
}

int UserDS::getUid()
{
    return this->uid;
}

int UserDS::getMoney()
{
    return this->money;
}

void UserDS::update(UserDS& user)
{
    this->username = user.getUsername();
    this->password = user.getPassword();
    this->userFlag = user.getUserFlag();
    this->tele     = user.getTele();
    this->userType = user.getUserType();
    this->uid = user.getUid();
    this->money = user.getMoney();
}

void UserDS::update(QString username, QString password, bool userFlag, QString tele, int money)
{
    this->username = username;
    this->password = password;
    this->userFlag = userFlag;
    this->tele = tele;
    this->money = money;
}

void UserDS::update(int uid, QString username, QString password, bool userFlag, QString tele, int money)
{
    this->username = username;
    this->password = password;
    this->userFlag = userFlag;
    this->tele = tele;
    this->uid = uid;
    this->money = money;
}


 void UserDS::update(QString username, QString password, bool userFlag, QString tele, int money, QString sellername)
{
    this->username = username;
    this->password = password;
    this->userFlag = userFlag;
    this->tele = tele;
    this->sellername = sellername;
    this->money = money;
}

void UserDS::update(int uid, QString username, QString password, bool userFlag, QString tele, int money, QString sellername)
{
    this->username = username;
    this->password = password;
    this->userFlag = userFlag;
    this->tele = tele;
    this->sellername = sellername;
    this->uid = uid;
    this->money = money;
}


void UserDS::update(int uid, QString username, QString password, bool userFlag, QString tele, int money, userDataType userType)
{
    this->username = username;
    this->password = password;
    this->userFlag = userFlag;
    this->tele = tele;
    this->userType = userType;
    this->uid = uid;
    this->money = money;
}

void UserDS::clear()
{
    update("", "", true, "", Invalid);
}

bool UserDS::isValidUsernamePattern()
{
    return isValidUsernamePattern(this->username);
}

bool UserDS::isValidPasswordPattern()
{
    return isValidPasswordPattern(this->password);
}

bool UserDS::isValidTelePattern()
{
    return isValidTelePattern(this->tele);
}

bool UserDS::isValidUsernamePattern(QString username)
{
    QRegularExpression re;
    re.setPattern("\\s");
    QRegularExpressionMatch match = re.match(username);

    if(match.hasMatch())
    {
        return false;
    }
    else
    {
        re.setPattern("^[a-zA-z0-9_\u4e00-\u9fa5]{2,20}$");
        match = re.match(username);
        if(match.hasMatch())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool UserDS::isValidPasswordPattern(QString password)
{
    QRegularExpression re;
    re.setPattern("\\s");
    QRegularExpressionMatch match = re.match(password);

    if(match.hasMatch())
    {
        return false;
    }
    else
    {
        re.setPattern("^\\w{6,10}$");
        match = re.match(password);
        if(match.hasMatch())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool UserDS::isValidTelePattern(QString tele)
{
    QRegularExpression re;

    re.setPattern("^\\s+");
    tele.replace(re, "");

    re.setPattern("\\s+$");
    tele.replace(re, "");

    re.setPattern("^[\\d]{3,15}$");
    QRegularExpressionMatch match = re.match(tele);
    if(match.hasMatch())
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString UserDS::userDataTypeStr(userDataType userType)
{
    switch(userType)
    {
        case Invalid:
            return "Invalid";
            break;
        case Valid:
            return "Valid";
            break;
        case ErrOpenDB:
            return "ErrOpenDB";
            break;
        case ErrSqlExec:
            return "ErrSqlExec";
            break;
        case ErrNoData:
            return "ErrNoData";
            break;
        case ErrMultiData:
            return "ErrMultiData";
            break;
        case ErrExistData:
            return "ErrExistData";
            break;
        default:
            return "Unknown";
    }
}


