#include "order.h"
#include "sqltool.h"
#include <QDebug>




Order::Order(QString id, QString datetime, QStringList productInfo)
{
    this->id = id;
    this->datetime = datetime;
    this->productInfo = productInfo;
    QSqlQuery query;
    SQLTool::search(query, "order_id", "orderInfo");
    query.last();
    this->orderID = query.value(0).toString();
}

Order::Order(){

}

void Order::editInfo(QString id, QString datetime, QStringList productInfo){
    this->id = id;
    this->datetime = datetime;
    this->productInfo = productInfo;
}

void Order::toString(QStringList &list){
    list.append(id);
    list.append(datetime);
    int n = this->productInfo.size();

    while(n){
        list.append(this->productInfo.at(n-2));
        list.append(this->productInfo.at(n-1));
        n -= 2;
    }
}

QStringList Order::getProductInfo(){
    QStringList list;
    int n = this->productInfo.size();
    while(n){
        list.append(this->productInfo.at(n-2));
        list.append(this->productInfo.at(n-1));
        n -= 2;
    }
    return list;
}

QString Order::getId(){
    return this->id;
}

QString Order::getDatetime(){
    return this->datetime;
}

void Order::info(QString orderID, QStringList &orderInformation)
{
    QSqlQuery query;
    SQLTool::search(query, "order", "ID", orderID);
    if(query.next()){
        orderInformation.append(query.value(0).toString());
        orderInformation.append(query.value(1).toString());
        orderInformation.append(query.value(2).toString());
    }

}

void Order::info(QVector<QStringList> &orderInformation)
{
    QSqlQuery query;
    SQLTool::search(query, "order");
    QStringList list;
    while (query.next()) {
        list.clear();
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        orderInformation.append(list);
    }
}


