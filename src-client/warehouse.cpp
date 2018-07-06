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

    QStringList list;

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
    QStringList list;


    QSqlQuery query;
    SQLTool::search(query, "arriving", "warehouse_id", QString::number(id));

    while(query.next()){
        QStringList list;
        list.append(query.value(2).toString());
        list.append(query.value(3).toString());
        result.insert(query.value(1).toString(), list);
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
        list.clear();
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        result.append(list);
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


void Warehouse::replenish(int id, QVector<Order>& orders){
    for(Order order : orders){
        QStringList list;
        order.getProductInfo(list);
        QString date_time = order.getDatetime();
        int n = list.size();
        while(n){
            QString clothes_id = list.at(n-2);
            QString quantity = list.at(n-1);
            QStringList result;
            result.append(QString::number(id));
            result.append(clothes_id);
            result.append(quantity);
            result.append(date_time);
            SQLTool::insert("arriving", result);

            n -= 2;
        }
    }
}










