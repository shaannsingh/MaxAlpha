#ifndef ORDERBOOK_H // Define these variables if not defined in build already
#define ORDERBOOK_H

#include <string>
#include <map>
#include <vector>
#include "order.h"

class OrderBook
{
private:
    std::map<double, std::vector<Order>> bids;
    std::map<double, std::vector<Order>> asks;
    bool cancelMapOrder(std::map<double, std::vector<Order>> &orderMap, int orderId);
    void displayBookHelper(const std::map<double, std::vector<Order>> &orderMap) const;

public:
    OrderBook();
    void addOrder(const Order &order);
    void cancelOrder(int orderId);
    double getHighestBid() const;
    double getLowestAsk() const;
    void displayBook() const;
};

#endif