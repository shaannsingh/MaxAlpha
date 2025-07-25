#ifndef MEANREVERSION_H
#define MEANREVERSION_H

#include <iostream>
#include "strategy.h"

class MeanReversion : public Strategy
{
protected:
    int observedPeriod, positionQuantity;
    double deviationThreshold;
    double findMovingAverage();

public:
    MeanReversion(int observed, double threshold, int position);
    Signal analyze(const MarketData &newTick) override;
    Order generateOrder(Signal signal, const MarketData &currentTick) override;
};

#endif