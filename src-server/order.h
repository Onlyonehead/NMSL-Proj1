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

    QStringList getProductInfo();

    QString getDatetime();

    static void info(QString orderID, QStringList &orderInformation);//return order info by ID

    static void info(QVector<QStringList> &orderInformation);//return all order info

    QString getId();

    //save order in providerOrder
    static void saveProviderOrder(QString providerOrderID, Order &providerOrder);

private:
    QString orderID;

    QString id;

    QString datetime;

    QStringList productInfo;

};

#endif // ORDER_H
