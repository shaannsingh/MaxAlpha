#ifndef MEANREVERSION_H
#define MEANREVERSION_H

#include <iostream>
#include "strategy.h"

class MeanReversion : public Strategy
{
protected:
    int movingAverageWindow;
    double deviationThreshold;
    double findMovingAverage();

public:
    MeanReversion(int moving, double threshold, int position);
    Signal analyze(const MarketData &newTick) override;
};

#endif