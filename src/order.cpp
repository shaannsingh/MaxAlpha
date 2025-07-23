#include <iostream>
#include "../include/order.h"

Order::Order(int i, char s, double p, int q, long t) : id(i), side(s), price(p), quantity(q), timestamp(t) {};

int Order::getOrderId() const
{
    return id;
}

char Order::getOrderSide() const
{
    return side;
}

double Order::getOrderPrice() const
{
    return price;
}

int Order::getOrderQuantity() const
{
    return quantity;
}

long Order::getOrderTime() const
{
    return timestamp;
}
