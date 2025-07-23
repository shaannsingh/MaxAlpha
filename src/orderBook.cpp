#include <iostream>
#include "../include/orderBook.h"

OrderBook::OrderBook() {
};

void OrderBook::addOrder(const Order &order)
{
    try
    {
        if (order.getOrderSide() == 'B')
        {
            bids[order.getOrderPrice()].push_back(order); // Adds order to bids map in Order vector
        }
        else if (order.getOrderSide() == 'S')
        {
            asks[order.getOrderPrice()].push_back(order); // Else, to asks
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error when adding order: " << e.what() << '\n';
    }
}

void OrderBook::cancelOrder(int orderId)
{
    if (cancelMapOrder(bids, orderId)) // Clean, readable, DRY
        return;
    if (cancelMapOrder(asks, orderId))
        return;
    std::cerr << "Error: Order #" << orderId << " could not be found." << "\n";
}

double OrderBook::getHighestBid() const
{
    if (bids.empty())
        return 0.0;
    return bids.rbegin()->first;
}

double OrderBook::getLowestAsk() const
{
    if (asks.empty())
        return 0.0;
    return asks.begin()->first;
}

void OrderBook::displayBook() const
{
    std::cout << "---- ORDER BOOK ----" << "\n";

    std::cout << "BIDS: " << "\n";
    displayBookHelper(bids);

    std::cout << "  ===== SPREAD =====" << "\n";

    std::cout << "ASKS: " << "\n";
    displayBookHelper(asks);

    std::cout << "---------------------" << "\n";
}

bool OrderBook::cancelMapOrder(std::map<double, std::vector<Order>> &orderMap, int orderId)
{
    for (auto &price : orderMap) // Look at each price level in the orderMap
    {
        auto &orders = price.second;                             // Get the orders
        for (auto it = orders.begin(); it != orders.end(); ++it) // Within orders of that level
        {
            if (it->getOrderId() == orderId) // If orderId matches
            {
                orders.erase(it); // Erase it
                if (orders.empty())
                {
                    orderMap.erase(price.first);
                }
                return true;
            }
        }
    }
    return false;
}

void OrderBook::displayBookHelper(const std::map<double, std::vector<Order>> &orderMap) const
{
    for (auto it = orderMap.rbegin(); it != orderMap.rend(); ++it)
    {
        int quantity = 0;
        for (const auto &order : it->second)
        {
            quantity += order.getOrderQuantity();
        }
        std::cout << " $" << it->first << " - " << quantity << " shares" << "\n";
    }
}
