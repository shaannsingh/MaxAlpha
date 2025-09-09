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
    double capital;
    double standardDeviation(std::vector<double> &returns);

public:
    Portfolio(double cash);
    void process(Order order);
    bool sufficientFunds(Order order);
    double getPortfolioValue(const double close);
    int getPortfolioShares();
    double sharpeRatio(double riskFreeRate, std::vector<double> returns);
    double calculatePnL();
};

#endif