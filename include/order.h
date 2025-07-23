#ifndef ORDER_H // Define these variables if not defined in build already
#define ORDER_H

#include <string>
#include <map>
#include <vector>

class Order // Order base class
{
private:
    int id;
    char side;
    double price;
    int quantity;
    long timestamp;

public:
    Order(int i, char s, double p, int q, long t); // Empty constructor to be initialized on order

    int getOrderId() const; // Values are not mutable
    char getOrderSide() const;
    double getOrderPrice() const;
    int getOrderQuantity() const;
    long getOrderTime() const;
};

#endif