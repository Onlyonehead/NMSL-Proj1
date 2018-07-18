#include "warehouse.h"

/**
 * return all warehouses' information
 *
 * @author Zicun Hang
 * @return information
 */
void Warehouse::info(QVector<QStringList> &result){
    QSqlQuery query;
    SQLTool::search(query, "warehouse");
    QStringList list;
    while(query.next()){
        list.clear();
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        list.append(query.value(3).toString());
        list.append(query.value(4).toString());
        list.append(query.value(5).toString());
        list.append(query.value(6).toString());
        list.append(query.value(7).toString());
        result.append(list);
    }
}


/**
 * return all warehouses' <id, name>
 *
 * @author Zicun Hang
 * @return information
 */
void Warehouse::info(QMap<QString, QString> &result){
    QSqlQuery query;
    SQLTool::search(query, "warehouse");
    QStringList list;
    while(query.next()){
        result.insert(query.value(0).toString(), query.value(1).toString());
    }
}

/**
 * return information of warehouse with given id
 *
 * @author Zicun Hang
 * @return information
 */
void Warehouse::info(int id, QStringList &result){
    QSqlQuery query;
    SQLTool::search(query, "warehouse", "id", QString::number(id));
    if(query.next()){
        result.append(query.value(0).toString());
        result.append(query.value(1).toString());
        result.append(query.value(2).toString());
        result.append(query.value(3).toString());
        result.append(query.value(4).toString());
        result.append(query.value(5).toString());
    }
}

/**
 * return stock information of warehouse with given id
 *
 * @author Zicun Hang
 * @return information
 */
void Warehouse::stock(int id, QMap<QString, QString> &result){

    QSqlQuery query;
    SQLTool::search(query, "stock", "warehouse_id", QString::number(id));

    while(query.next()){
        result.insert(query.value(1).toString(), query.value(2).toString());
    }
}

/**
 * return arriving information of warehouse with given id
 *
 * @author Zicun Hang
 * @return information
 */
void Warehouse::arriving(int id, QMap<QString,QStringList> &result){
    QSqlQuery query;
    SQLTool::search(query, "arriving", "warehouse_id", QString::number(id));

    while(query.next()){
        QStringList list;
        list.append(query.value(2).toString());
        list.append(query.value(3).toString());
        result.insert(query.value(1).toString(), list);
        list.clear();
    }
}


/**
 * return all warehouses' stock information
 *
 * @author Zicun Hang
 * @return information
 */
void Warehouse::stock(QVector<QStringList> &result){

    QStringList list;
    QSqlQuery query;
    SQLTool::search(query, "stock");
    while(query.next()){
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        result.append(list);
        list.clear();
    }
}

/**
 * return all warehouses' stock information with classification
 *
 * @author Zicun Hang
 * @return information
 */
void Warehouse::stock(QMap<QString,QMap<QString, QString>> &result){
    QMap<QString, QString> map;
    QSqlQuery query;
    SQLTool::search(query, "warehouse");
    while(query.next()){
        stock(query.value(0).toInt(), map);
        result.insert(query.value(0).toString(), map);
        map.clear();
    }
}


/**
 * return all warehouses' arriving information
 *
 * @author Zicun Hang
 * @return information
 */
void Warehouse::arriving(QVector<QStringList> &result){
    QStringList list;

    QSqlQuery query;
    SQLTool::search(query, "arriving");

    while(query.next()){
        list.clear();
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        list.append(query.value(3).toString());
        result.append(list);
    }
}

/**
 * return all warehouses' arriving information with classification
 *
 * @author Zicun Hang
 * @return information
 */
void Warehouse::arriving(QMap<QString, QMap<QString, QStringList>> &result){
    QMap<QString, QStringList> map;
    QSqlQuery query;
    SQLTool::search(query, "warehouse");
    while(query.next()){
        arriving(query.value(0).toInt(), map);
        result.insert(query.value(0).toString(), map);
        map.clear();
    }
}

void Warehouse::sendRequirement(Order &order){
    Logistics::receiveOrder(order);
}

void Warehouse::replenish(QString id, Order& order){
    QStringList list;
    QString goods;
    list = order.getProductInfo();
    QString date_time = order.getDatetime();
    QString from_id = order.getId();
    int n = list.size();
    while(n){
        QString clothes_id = list.at(n-2);
        QString quantity = list.at(n-1);
        QStringList result;
        result.append(id);
        result.append(clothes_id);
        result.append(quantity);
        result.append(date_time);
        result.append(from_id);
        SQLTool::insert("arriving", result);

        n -= 2;

        QStringList l2;
        Warehouse::GInfo(clothes_id.toInt(),l2);
        goods += clothes_id + " - " + l2.at(1) + "  quantity: " + quantity + "\n";
    }

//    QStringList sqlist;
//    sqlist.append(order.getDatetime());
//    sqlist.append(order.getId());
//    sqlist.append(id);
//    sqlist.append(goods);
//    SQLTool::insert("wh_history",sqlist);
}

void Warehouse::deliverGoods(QString id, Order& order){
    QStringList list;
    QString goods;
    list = order.getProductInfo();
    int n = list.size();
    while(n){
        QSqlQuery query;
        QString clothes_id = list.at(n-2);
        QString quantity = list.at(n-1);
        QStringList l;
        l.append("warehouse_id");
        l.append(id);
        l.append("clothes_id");
        l.append(clothes_id);
        SQLTool::search(query,"quantity", "stock", l);
        query.next();
        SQLTool::update("stock", "quantity",QString::number(
                            query.value(0).toInt() - quantity.toInt()), l);
        n -= 2;
        QStringList l2;
        Warehouse::GInfo(clothes_id.toInt(),l2);
        goods += clothes_id + " - " + l2.at(1) + "  quantity: " + quantity + "\n";
    }

    QStringList sqlist;
    sqlist.append(order.getDatetime());
    sqlist.append(id);
    sqlist.append(order.getId());
    sqlist.append(goods);
    SQLTool::insert("wh_history",sqlist);
}


/**
 * transfer arriving clothes to stock
 *
 * @author Zicun Hang
 */
void Warehouse::transfer(){
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString till_time = current_date_time.addSecs(300).toString("yyyy-MM-dd hh:mm:ss");

    QSqlQuery query, query2;

    SQLTool::search(query, "arriving");
    while(query.next()){

        QString arrive_date = query.value(3).toString();

        QStringList s = arrive_date.split(QRegExp("[-A-Z:]"));
        int year = s[0].toInt();
        int month = s[1].toInt();
        int day = s[2].toInt();
        int hour = s[3].toInt();
        int minute = s[4].toInt();
        int second = s[5].toInt();
        QTime time;
        time.setHMS(hour,minute,second);
        QDate date;
        date.setDate(year, month, day);
        QDateTime arrive_datetime;
        arrive_datetime.setDate(date);
        arrive_datetime.setTime(time);

        if(arrive_datetime < current_date_time){
            QString warehouse_id = query.value(0).toString();
            QString clothes_id = query.value(1).toString();
            int quantity = query.value(2).toInt();
            QStringList list;
            list.append("warehouse_id");
            list.append(warehouse_id);
            list.append("clothes_id");
            list.append(clothes_id);
            SQLTool::search(query2, "quantity", "stock", list);
            SQLTool::del("arriving", list);
            if(query2.next()){
                int stock = query2.value(0).toInt();
                SQLTool::update("stock", "quantity",
                                QString::number(stock + quantity), list);
            }else{
                list.clear();
                list.append(query.value(0).toString());
                list.append(query.value(1).toString());
                list.append(query.value(2).toString());
                SQLTool::insert("stock", list);
            }

        }

    }
    SQLTool::del("stock", "quantity", "0");
}

void Warehouse::GInfo(QVector<QStringList> &garmentInfo)
{
    QSqlQuery query;
    SQLTool::search(query, "clothes");
    QStringList list;
    while (query.next()) {
        list.clear();
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        list.append(query.value(3).toString());
        list.append(query.value(4).toString());
        garmentInfo.append(list);
    }
}

void Warehouse::GInfo(int i, QStringList &garmentInfo)
{
    QString ID = QString::number(i, 10);
    QSqlQuery query;
    SQLTool::search(query, "clothes", "ID", ID);
    if(query.next()){
        garmentInfo.append(query.value(0).toString());
        garmentInfo.append(query.value(1).toString());
        garmentInfo.append(query.value(2).toString());
        garmentInfo.append(query.value(3).toString());
        garmentInfo.append(query.value(4).toString());
    }
}




