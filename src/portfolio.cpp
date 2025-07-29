#include <iostream>
#include <numeric>
#include "../include/portfolio.h"

Portfolio::Portfolio(double cash) : capital(cash) {};

void Portfolio::process(Order order)
{
    orders.push_back(order);
}

double Portfolio::calculatePnL()
{
    double pnl = 0.0;

    for (const auto &order : orders)
    {
        double position = order.getOrderPrice() * order.getOrderQuantity();
        pnl += (order.getOrderSide() == 'S') ? position : -position;
    }

    return pnl;
}

double Portfolio::calculateSharpeRatio(double riskFreeRate)
{
}