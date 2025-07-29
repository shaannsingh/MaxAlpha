#include <iostream>
#include "strategies/bollinger.h"
#include <numeric>
#include <algorithm>

Bollinger::Bollinger(double multiplier, int position) : deviationMultiplier(multiplier), Strategy(position) {};

Signal Bollinger::analyze(const MarketData &currentTick)
{
    data.push_back(currentTick);
    if (data.size() < 20)
        return HOLD;

    double middleBand = findMovingAverage(20);
    double standardDeviation = calculateStandardDeviation(data);

    upperBand = middleBand + (deviationMultiplier * standardDeviation);
    lowerBand = middleBand - (deviationMultiplier * standardDeviation);

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

double Bollinger::calculateStandardDeviation(std::vector<MarketData> &data)
{
    double sum, mean, variance, standardDeviation;

    sum = 0.0;
    variance = 0.0;
    int start = data.size() - 20;

    for (int i = start; i < data.size(); i++)
    {
        sum += data[i].close;
    }
    mean = sum / 20;

    for (int i = start; i < data.size(); i++)
    {
        double deviation = data[i].close - mean;
        variance += deviation * deviation;
    }
    variance /= 20;

    return sqrt(variance);
}
