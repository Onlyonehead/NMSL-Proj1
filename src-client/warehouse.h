#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QWidget>
#include <QFont>
#include <QTabBar>

#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QFontDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "sqltool.h"
#include "order.h"


class Warehouse{

public:
    //出货
//    static void generateDeliveryOrder(Order &order);

    //返回id对应仓库的库存
    static void stock(int, QMap<QString, QString> &);

    //返回所有仓库的 <id, name>
    static void info(QMap<QString, QString> &);

    //返回id对应仓库的即将到货
    static void arriving(int, QMap<QString,QStringList> &);

    //返回id对应仓库的详细信息
    static void info(int, QStringList&);

    //返回所有仓库的库存
    static void stock(QVector<QStringList>&);

    //返回所有仓库的即将到货
    static void arriving(QVector<QStringList>&);

    //返回所有仓库的详细信息
    static void info(QVector<QStringList>&);

    //补货
    static void replenish(int, QVector<Order>&);
};


#endif // WAREHOUSE_H
