#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <iostream>
#include <vector>
#include <string>
#include "order.h"

class Portfolio
{
private:
    std::vector<Order> orders;
    double capital, portfolioValue;
    double calculateDailyReturns();
    double calculateStandardDeviation(std::vector<Order> &orders);

public:
    Portfolio(double cash);
    void process(Order order);
    double calculatePnL();
    double calculateSharpeRatio(double riskFreeRate);
    void getPortfolioValue();
    void addDailyReturn(const double price);
};

#endif