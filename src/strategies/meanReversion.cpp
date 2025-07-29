#include <iostream>
#include "strategies/meanReversion.h"

MeanReversion::MeanReversion(int moving, double threshold, int position) : movingAverageWindow(moving), deviationThreshold(threshold), Strategy(position) {};

Signal MeanReversion::analyze(const MarketData &currentTick)
{
    data.push_back(currentTick);

    if (data.size() < movingAverageWindow)
        return HOLD;

    double movingAverage = findMovingAverage(movingAverageWindow);
    double deviation = ((currentTick.close - movingAverage) / movingAverage) * 100;

    if (deviation < -deviationThreshold)
        return BUY;
    if (deviation > deviationThreshold)
        return SELL;
    return HOLD;
};