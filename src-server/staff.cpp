#include "staff.h"
#include "sqltool.h"
#include <QDebug>
#include <QList>
#include <QSqlQuery>


Staff::Staff()
{

}

/**
  * add new staff information to database
  *
  * @author Yihan Dong
  * @return void
*/

void Staff::addNewStaff(QString username, QString password,
                        QString name, QString gender, QString email, QString position, QString userPic)
{

    QStringList staffInfo;
    staffInfo.append(username);
    staffInfo.append(password);
    staffInfo.append(name);
    staffInfo.append(gender);
    staffInfo.append(position);
    staffInfo.append(email);
    staffInfo.append(userPic);
    SQLTool::insert("userdata", staffInfo);
}



/**
  * return all staffs information
  *
  * @author Yihan Dong
  * @return information
*/


void Staff::Info(QVector<QStringList> &staffInfo)
{
    QSqlQuery query;
    QStringList list;
    SQLTool::search(query, "userdata");
    while (query.next()) {
        list.clear();
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        list.append(query.value(3).toString());
        list.append(query.value(4).toString());
        list.append(query.value(5).toString());
        list.append(query.value(6).toString());
        staffInfo.append(list);
    }
}


/**
  * return staff inforamtion by other attributes
  *
  * @author Yihan Dong
  * @return information
*/


void Staff::Info(QString searchAttribute, QString searchValue, QVector<QStringList> &staffInfo)
{
    QSqlQuery query;
    QStringList list;
    SQLTool::fuzzySearch(query, "userdata", searchAttribute, searchValue);
    while (query.next()) {
        list.clear();
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        list.append(query.value(3).toString());
        list.append(query.value(4).toString());
        list.append(query.value(5).toString());
        list.append(query.value(6).toString());
        staffInfo.append(list);
    }
}


/**
  * update staff information by username
  *
  * @author Yihan Dong
  * @return void
*/


void Staff::updateStaffInfo(QString username, QString alterAttribute, QString alterValue)
{
    QStringList alterUsername;
    alterUsername.append("username");
    alterUsername.append(username);
    SQLTool::update("userdata", alterAttribute, alterValue, alterUsername);
}

/**
  * update staff username by email
  *
  * @author Yihan Dong
  * @return void
*/


void Staff::alterStaffUsername(QString email, QString alterUsername)
{
    QStringList alterEmail;
    alterEmail.append("email");
    alterEmail.append(email);
    SQLTool::update("userdata", "username", alterUsername, alterEmail);
}

/**
  * delete staff information by username
  *
  * @author Yihan Dong
  * @return void
*/


void Staff::deleteStaffInfo(QString username)
{
    SQLTool::del("userdata", "username", username);
}

/**
 * check if username is existed
 *
 * @author Yihan Dong
 * @return bool
*/

bool Staff::isUsernameExisted(QString username)
{
    QSqlQuery query;
    SQLTool::search(query, "username", "userdata", "username", username);
    if(query.next()){
        return true;
    }else{
        return false;
    }

}


/**
 * @brief Staff::isEmailExisted
 * check if email is existed
 * @author Yihan Dong
 * @param email
 * @return bool
 */


bool Staff::isEmailExisted(QString email)
{
    QSqlQuery query;
    SQLTool::search(query, "email", "userdata", "email", email);
    if(query.next()){
        return true;
    }else {
        return false;
    }
}
