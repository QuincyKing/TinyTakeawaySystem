#include "reguserdb.h"

RegUserDB::RegUserDB()
{
}

bool RegUserDB::searchUserByUsername(UserDS& user)
{
    bool result = false;

    if(!connDB())
    {
        user.setUserType(UserDS::ErrOpenDB);
        return false;
    }

    QSqlQuery myQuery;
    myQuery.prepare("SELECT * FROM Buyer, Seller WHERE Buyer.B_name=:name_b or Seller.S_name=:name_s;");
    myQuery.bindValue(":name_b", user.getUsername());
    myQuery.bindValue(":name_s", user.getUsername());

    if(!myQuery.exec())
    {
        user.setUserType(UserDS::ErrSqlExec);
    }
    else
    {
        result = myQuery.next();
        if(!result)
        {
            user.setUserType(UserDS::ErrNoData);
        }
    }

    myQuery.clear();
    disconnDB();

    return result;
}

bool RegUserDB::authUser(UserDS& user)
{
    return searchUserByUsernameAndPassword(user);
}

bool RegUserDB::searchUserByUsernameAndPassword(UserDS& user)
{
    bool result = false;

    if(!searchUserByUsername(user))
    {
        result = false;
    }
    else
    {
        if(!connDB())
        {
            user.setUserType(UserDS::ErrOpenDB);
            return false;
        }

        QSqlQuery buyerQuery;
        buyerQuery.prepare(
                QString("SELECT * FROM Buyer WHERE B_name = '%1' and B_pwd = '%2';")
                .arg(user.getUsername()).arg(user.getPassword())
                );

        QSqlQuery sellerQuery;
        sellerQuery.prepare(
                QString("SELECT * FROM Seller WHERE S_name = '%1' and S_pwd = '%2';")
                .arg(user.getUsername()).arg(user.getPassword())
                );

        if(!buyerQuery.exec()||!sellerQuery.exec())
        {

            user.setUserType(UserDS::ErrSqlExec);
        }
        else
        {
            int i = 0;

            if(buyerQuery.next())
            {
                do
                {
                    user.update(buyerQuery.value(0).toInt(), buyerQuery.value(2).toString(), buyerQuery.value(1).toString(), true,
                                buyerQuery.value(4).toString(), buyerQuery.value(5).toInt());

                    if(i == 0)
                    {
                        result = true;
                        user.setUserType(UserDS::Valid);
                    }
                    else
                    {
                        result = false;
                        user.setUserType(UserDS::ErrMultiData);
                    }
                    i++;
                }while(buyerQuery.next());
            }
            else if(sellerQuery.next())
            {
                do
                {
                    user.update(sellerQuery.value(0).toInt(), sellerQuery.value(2).toString(), sellerQuery.value(1).toString(), false,
                                sellerQuery.value(5).toString(), sellerQuery.value(6).toInt(), sellerQuery.value(3).toString());

                    if(i == 0)
                    {
                        result = true;
                        user.setUserType(UserDS::Valid);
                    }
                    else
                    {
                        result = false;
                        user.setUserType(UserDS::ErrMultiData);
                    }
                    i++;
                } while(sellerQuery.next());
            }
            if( i == 0 )
            {
                user.setUserType(UserDS::ErrNoData);
            }
        }

        buyerQuery.clear();
        sellerQuery.clear();
        disconnDB();
    }

    return result;
}

bool RegUserDB::addUser(UserDS& user)
{
    bool result = false;

    if(searchUserByUsername(user))
    {
        user.setUserType(UserDS::ErrExistData);
        result = false;
    }
    else
    {

        if(!connDB())
        {
            user.setUserType(UserDS::ErrOpenDB);
            return false;
        }

        QSqlQuery myQuery;
        if(user.getUserFlag())
        {
            myQuery.prepare(
                QString("insert into Buyer (B_name, B_pwd, B_tel, B_money) values (:name, :pwd, :tel, 0);")
            );
            myQuery.bindValue(":name", user.getUsername());
            myQuery.bindValue(":pwd", user.getPassword());
            myQuery.bindValue(":tel", user.getTele());
        }
        else
        {
            myQuery.prepare(
                QString("insert into Seller (S_name, S_pwd, S_tel, S_money, S_shopname) values (:name, :pwd, :tel, 0, :shopname);")
            );
            myQuery.bindValue(":name", user.getUsername());
            myQuery.bindValue(":pwd", user.getPassword());
            myQuery.bindValue(":tel", user.getTele());
            myQuery.bindValue(":shopname", user.getSellername());
        }


        if(myQuery.exec())
        {
            user.setUserType(UserDS::Valid);
            result = true;
        }
        else
        {
            user.setUserType(UserDS::ErrSqlExec);
            result = false;
        }

        myQuery.clear();
        disconnDB();
    }

    return result;
}
