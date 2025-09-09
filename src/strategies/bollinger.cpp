#include <iostream>
#include "strategies/bollinger.h"
#include <numeric>
#include <algorithm>

Bollinger::Bollinger(double multiplier, int position) : Strategy(position), deviationMultiplier(multiplier) {};

Signal Bollinger::analyze(const MarketData &currentTick)
{
    data.push_back(currentTick);
    if (data.size() < 20)
        return HOLD;

    double middleBand = findMovingAverage(20);
    double stdDev = standardDeviation(data);

    upperBand = middleBand + (deviationMultiplier * stdDev);
    lowerBand = middleBand - (deviationMultiplier * stdDev);

    double price = currentTick.close;

    if (price >= upperBand)
    {
        return SELL; // Overbought, sell
    }
    else if (price <= lowerBand)
    {
        return BUY; // Underbought, buy
    }
    else
    {
        return HOLD;
    }
}

double Bollinger::standardDeviation(std::vector<MarketData> &data)
{
    double sum = 0.0;
    double variance = 0.0;
    int start = data.size() - 20;

    for (size_t i = start; i < data.size(); i++)
    {
        sum += data[i].close;
    }
    double mean = sum / 20;

    for (size_t i = start; i < data.size(); i++)
    {
        double deviation = data[i].close - mean;
        variance += deviation * deviation;
    }
    variance /= 20;

    return sqrt(variance);
}
