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
    double calculateStandardDeviation(std::vector<Order> &data);

public:
    Portfolio(double cash);
    void process(Order order);
    double calculatePnL();
    double calculateSharpeRatio(double riskFreeRate);
};

#endif