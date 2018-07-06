#include "login.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include "systemcenter.h"
#include "order.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QStringList list1, list2;
//    list1.append("1");
//    list1.append("100");
//    list1.append("3");
//    list1.append("300");
//    list2.append("2");
//    list2.append("200");

//    Order order1(5, "2020-03-03 12:22:21", list1);

//    Order order2(6, "2020-03-03 12:22:21", list2);

//    QVector<Order> orders;
//    orders.append(order1);
//    orders.append(order2);

//    Warehouse::replenish(4,orders);

    Login *w = new Login;
//    FtpClient client;
//    client.FtpSetHostPort("ftp://39.108.155.50");
//    client.FtpSetUserInfo("root", "abcd1234");
//    client.FtpGet("/project1/clothes/a.jpg", "/Users/Haibara/Desktop/a.jpg");
    w->show();

    return a.exec();
}
