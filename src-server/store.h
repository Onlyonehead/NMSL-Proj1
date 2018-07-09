#ifndef STORE_H
#define STORE_H

#include "TCPConnection.h"
#include "record.h"
#include <QVector>

class Store{
public:
    static QString getPicPath(QString);
    static QString getClothStyle(QString id);
    static QStringList getClothDetail(QString id);
    static void getAllClothes(QVector<QStringList>&);
    static QVector<QString> getStoreInfo(QString, QString);
    static QVector<QVector<QString>> getStock(QString);
    static QVector<Record> getRecord(int ,int&);
    static bool sellGoods(QString, QString, QVector<int>);
};

#endif // STORE_H
