#ifndef STORE_H
#define STORE_H

#include "TCPConnection.h"
#include "record.h"
#include <QVector>

class Store{
public:
    static QString getPicPath(QString);
    static QString getClothStyle(QString id);
    static void getClothDetail(QString id, QStringList&);
    static void getAllClothes(QVector<QStringList>&);
    static void getStoreInfo(QString, QString, QVector<QString>&);
    static void getStock(QString, QVector<QVector<QString>>&);
    static void getRecord(int ,int&, QVector<Record>&);
    static void getStores(QVector<QStringList>&);
    static bool sellGoods(QString, QString, QVector<int>);
};

#endif // STORE_H
