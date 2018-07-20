#include "order.h"
#include "sqltool.h"
#include <QDebug>



/**
 * constructor
 *
 * @author hzc
 * @param id order id
 * @param datetime time of order
 * @param productInfo product infomation of this order
 */

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

/**
 * edit information of this order
 *
 * @author hzc
 * @param id order id
 * @param datetime time of this order
 * @param productInfo product information of this order
 */

void Order::editInfo(QString id, QString datetime, QStringList productInfo){
    this->id = id;
    this->datetime = datetime;
    this->productInfo = productInfo;
}

/**
 * convert order information to string
 *
 * @author hzc
 * @param list
 */
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

/**
 * get product information of this order
 *
 * @author hzc
 * @return list of information
 */
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

/**
 * get id of this order
 *
 * @author hzc
 * @return id
 */
QString Order::getId(){
    return this->id;
}

/**
 * get datetime of this order
 *
 * @author hzc
 * @return datetime
 */
QString Order::getDatetime(){
    return this->datetime;
}



/**
 * save order from provider
 *
 * @author Dong Yihan
 * @param providerOrderID id of this order
 * @param providerOrder this order
 */
void Order::saveProviderOrder(QString providerOrderID, Order &providerOrder)
{
    QStringList list;
    QString providerID = providerOrder.getId();
    QString datetime = providerOrder.getDatetime();
    QStringList providerTempInfo = providerOrder.getProductInfo();
    QString providerInfo = providerTempInfo.join("#");
    list.append(providerOrderID);
    list.append(providerID);
    list.append(datetime);
    list.append(providerInfo);
    SQLTool::insert("providerOrder", list);
}

/**
 * return information with given id
 *
 * @author Dong Yihan
 * @param orderID id of this order
 * @param orderInformation
 */
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

/**
 * return information of all orders
 *
 * @author Dong Yihan
 * @param orderInformation
 */
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


