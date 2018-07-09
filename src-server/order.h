#ifndef ORDER_H
#define ORDER_H
#include <QString>
#include <QStringList>
#include <QVector>


class Order
{

public:
    Order(int id, QString datetime, QStringList productInfo);
    Order();

    void editInfo(int id, QString datetime, QStringList productInfo);

    void toString(QStringList &);

    void getProductInfo(QStringList &);

    QString getDatetime();

    static void saveOrder(Order&);

    static void info(QString orderID, QStringList &orderInformation);//return order info by ID

    static void info(QVector<QStringList> &orderInformation);//return all order info

private:
    int orderID;

    int id;

    QString datetime;

    QStringList productInfo;

};

#endif // ORDER_H
