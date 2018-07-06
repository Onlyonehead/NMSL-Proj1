#ifndef LOGIN_H
#define LOGIN_H

#include "TCPConnection.h"

class Login : public QWidget
{
public:
    static int login(QString username, QString password);
    static QStringList info(QString);
};

#endif // LOGIN_H
