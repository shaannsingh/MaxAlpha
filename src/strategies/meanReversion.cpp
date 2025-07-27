#include <iostream>
#include "strategies/meanReversion.h"

MeanReversion::MeanReversion(int moving, double threshold, int position) : movingAverageWindow(moving), deviationThreshold(threshold)
{
    this->positionQuantity = position;
};

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

double MeanReversion::findMovingAverage()
{
    double sum = 0.0;

    for (int i = (int)(data.size() - movingAverageWindow); i < data.size(); i++)
    {
        sum += data[i].close;
    }

    return sum / movingAverageWindow;
}