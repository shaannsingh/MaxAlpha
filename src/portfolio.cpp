#include <iostream>
#include <numeric>
#include "../include/portfolio.h"

Portfolio::Portfolio(double cash) : capital(cash) {};

void Portfolio::process(Order order)
{
    orders.push_back(order);
}

bool Portfolio::sufficientFunds(Order order)
{
    double orderValue = order.getOrderPrice() * order.getOrderQuantity();

    if (order.getOrderSide() == 'B')
    {
        double cash = capital + calculatePnL();
        return cash >= orderValue;
    }
    else
    {
        int shares = getPortfolioShares();
        return shares >= order.getOrderQuantity();
    }
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

double Portfolio::sharpeRatio(double riskFreeRate, std::vector<double> returns, const double currentPrice)
{
    double portfolioValue = getPortfolioValue(currentPrice);
    double returnValue = (portfolioValue - capital) / capital;
    double volatility = standardDeviation(returns);

    std::cout << "DEBUG - Number of daily returns: " << returns.size() << std::endl;
    std::cout << "DEBUG - Sample daily returns: ";
    for (int i = 0; i < std::min(5, (int)returns.size()); i++)
    {
        std::cout << returns[i] * 100 << "%, ";
    }
    std::cout << std::endl;
    std::cout << "DEBUG - Time period: " << returns.size() << " days" << std::endl;
    std::cout << "DEBUG - Total Return: " << returnValue << std::endl;
    std::cout << "DEBUG - Volatility: " << volatility << std::endl;
    std::cout << "DEBUG - Risk-free rate: " << riskFreeRate << std::endl;

    return (returnValue - riskFreeRate) / volatility;
};

double Portfolio::standardDeviation(std::vector<double> &returns)
{
    if (returns.empty())
        return 0.0;

    double sum = 0.0;
    double variance = 0.0;

    for (const auto &r : returns)
    {
        sum += r;
    }
    double mean = sum / (returns.size());

    for (int i = 0; i < returns.size(); i++)
    {
        double deviation = returns[i] - mean;
        variance += deviation * deviation;
    }
    variance /= returns.size();

    return sqrt(variance);
};

double Portfolio::getPortfolioValue(double close)
{
    double shares = 0;
    for (const auto &order : orders)
    {
        double quantity = order.getOrderQuantity();
        shares += (order.getOrderSide() == 'B') ? quantity : -quantity;
    }
    double cash = capital + calculatePnL();
    return cash + (shares * close);
};

int Portfolio::getPortfolioShares()
{
    int shares = 0;
    for (const auto &order : orders)
    {
        shares += (order.getOrderSide() == 'B') ? order.getOrderQuantity() : -order.getOrderQuantity();
    }
    return shares;
}