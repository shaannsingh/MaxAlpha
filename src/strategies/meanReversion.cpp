#include <iostream>
#include "strategies/meanReversion.h"

MeanReversion::MeanReversion(int moving, double threshold, int position) : movingAverageWindow(moving), deviationThreshold(threshold), positionQuantity(position) {};

Signal MeanReversion::analyze(const MarketData &nextTick)
{
    data.push_back(nextTick);

    if (data.size() < movingAverageWindow)
        return HOLD;

    double movingAverage = findMovingAverage();
    double deviation = ((nextTick.close - movingAverage) / movingAverage) * 100;

    if (deviation < -deviationThreshold)
        return BUY;
    if (deviation > deviationThreshold)
        return SELL;
    return HOLD;
};

Order MeanReversion::generateOrder(Signal signal, const MarketData &currentTick)
{
    orderCount++;
    char side = (signal == BUY ? 'B' : 'S');
    double price = currentTick.close;
    int quantity = positionQuantity;
    long timestamp = currentTick.timestamp;
    int id = orderCount;
    return Order(id, side, price, quantity, timestamp);
}

double MeanReversion::findMovingAverage()
{
    double sum = 0.0;

    for (int i = (int)(data.size() - movingAverageWindow); i < data.size(); i++)
    {
        sum += data[i].close;
    }

    return sum / movingAverageWindow;
}