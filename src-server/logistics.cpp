#include "logistics.h"


Logistics::Logistics()
{

}


void Logistics::receiveOrder(Order &order){
    Order::saveOrder(order);
}

