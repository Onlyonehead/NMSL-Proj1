#ifndef STAFF_H
#define STAFF_H
#include <QString>
#include <QStringList>
#include <QVector>


class Staff
{
public:
    Staff();

    //add new staff to database
    static void addNewStaff(QString username, QString password,
                     QString name, QString gender, QString email, QString userPic);

    //return all staffs' information
    static void Info(QVector<QStringList> &staffInfo);

    //return staff information multi
    static void Info(QString searchAttribute, QString searchValue, QVector<QStringList> &staffInfo);

    //return staff information signle
    static void Info(QString searchAttribute, QString searchValue, QStringList &staffInfo);

    //update staff information by username
    static void updateStaffInfo(QString username, QString alterAttribute, QString alterValue);

    //alter staff username by email
    static void alterStaffUsername(QString email, QString alterUsername);

    //YOU ARE DISMISSED!
    static void deleteStaffInfo(QString username);

    //check if username is existed
    static bool isUsernameExisted(QString username);

    //check is email is existed
    static bool isEmailExisted(QString email);
private:
    QString username;

    QString password;

    QString name;

    QString gender;

    QString email;

    QString userPic;
};

#endif // STAFF_H
