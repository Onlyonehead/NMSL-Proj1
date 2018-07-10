#include "logistics.h"


Logistics::Logistics()
{

}


void Logistics::receiveOrder(Order &order)
{
    Logistics::saveOrder(order);
}


void Logistics::saveOrder(Order &order)
{
    QStringList list;
    QString productInformation;
    productInformation = order.getProductInfo().join("#");
    list.append("0");
    list.append(order.getId());
    list.append(order.getDatetime());
    list.append(productInformation);
    SQLTool::insert("orderInfo", list);
}
