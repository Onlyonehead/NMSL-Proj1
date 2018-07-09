#ifndef ORDER_H
#define ORDER_H
#include <QString>
#include <QStringList>
#include <QVector>


class Order
{

public:
    Order(QString id, QString datetime, QStringList productInfo);
    Order();

    void editInfo(QString id, QString datetime, QStringList productInfo);

    void toString(QStringList &);

    void getProductInfo(QStringList &);

    QString getDatetime();

    static void saveOrder(Order&);

    static void info(QString orderID, QStringList &orderInformation);//return order info by ID

    static void info(QVector<QStringList> &orderInformation);//return all order info

    QString getId();

private:
    QString orderID;

    QString id;

    QString datetime;

    QStringList productInfo;

};

#endif // ORDER_H
