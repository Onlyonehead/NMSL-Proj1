#ifndef PROVIDER_H
#define PROVIDER_H
#include "order.h"
#include <QString>
#include <QStringList>
#include <QVector>



class Provider
{
public:
    Provider();

    //add new provider information to database
    static void addNewPrvider(QString providerName, QString providerAddress, QString produceInfo);

    //search provider information by provider ID
    static void Info(int providerID, QStringList &providerInfo);

    //return all providers information
    static void Info(QVector<QStringList> &ProviderInfo);

    //receive order from corporation
    void receiveOrder(Order order);

    //update provider information
    static void updateProviderInfo(int ID, QString alterAttribute, QString alterValue);


private:
    int ID;

    QString address;

    QString name;

    QStringList produceInfo;
};

#endif // PROVIDER_H
