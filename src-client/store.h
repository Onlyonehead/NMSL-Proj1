#ifndef STORE_H
#define STORE_H

#include "record.h"
#include <QVector>

class Store{
public:
    static QString getPicPath(QString);
    static QString getClothStyle(QString id);
    static void getStoreInfo(QString, int, QVector<QString>&);
    static void getStock(int, QVector<QVector<QString>>&);
    static void getRecord(int &, int&, QVector<Record>&);
    static bool sellGoods(int, double, QVector<int>);
};

#endif // STORE_H
