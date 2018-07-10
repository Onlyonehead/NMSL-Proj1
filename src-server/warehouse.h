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
#include <QTime>
#include <QDateTime>
#include <QDate>
#include <QCompleter>
#include <QStringListModel>
#include "sqltool.h"
#include "order.h"
#include "logistics.h"


class Warehouse{

public:
    //出货
//    static void generateDeliveryOrder(Order &order);



    //返回所有仓库的 <id, name>
    static void info(QMap<QString, QString> &);

    //返回id对应仓库的详细信息
    static void info(int, QStringList&);

    //返回所有仓库的详细信息
    static void info(QVector<QStringList>&);

    //返回id对应仓库的库存
    static void stock(int, QMap<QString, QString> &);


    //返回所有仓库的库存
    static void stock(QVector<QStringList>&);

    //返回所有仓库的库存(按id归类)
    static void stock(QMap<QString,QMap<QString, QString>> &);




    //返回id对应仓库的即将到货
    static void arriving(int, QMap<QString,QStringList> &);

    //返回所有仓库的即将到货
    static void arriving(QVector<QStringList>&);

    //返回所有仓库的即将到货(按id归类)
    static void arriving(QMap<QString, QMap<QString, QStringList>> &);

    //transfer arriving clothes to stock
    static void transfer();



    //补货
    static void replenish(QString, Order&);

    //发送订单请求
    static void sendRequirement(Order &order);

    //发货
    static void deliverGoods(QString, Order&);

    static void GInfo(QVector<QStringList> &);
    static void GInfo(int, QStringList &);
};



#endif // WAREHOUSE_H
