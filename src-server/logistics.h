#ifndef LOGISTICS_H
#define LOGISTICS_H

#include "order.h"
#include "sqltool.h"


class Logistics
{
public:
    Logistics();
    static void receiveOrder(Order &order);
    static void saveOrder(Order &order);
};

#endif // LOGISTICS_H
