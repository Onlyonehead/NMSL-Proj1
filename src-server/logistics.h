#ifndef LOGISTICS_H
#define LOGISTICS_H

#include "order.h"


class Logistics
{
public:
    Logistics();
    static void receiveOrder(Order &order);
};

#endif // LOGISTICS_H
