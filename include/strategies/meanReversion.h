#ifndef MEANREVERSION_H
#define MEANREVERSION_H

#include <iostream>
#include "strategy.h"

class MeanReversion : public Strategy
{
protected:
    int movingAverageWindow, positionQuantity;
    double deviationThreshold;
    double findMovingAverage();

public:
    MeanReversion(int moving, double threshold, int position);
    Signal analyze(const MarketData &newTick) override;
    Order generateOrder(Signal signal, const MarketData &currentTick) override;
};

#endif