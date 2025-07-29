#ifndef MEANREVERSION_H
#define MEANREVERSION_H

#include <iostream>
#include "strategy.h"

class MeanReversion : public Strategy
{
protected:
    int movingAverageWindow;
    double deviationThreshold;

public:
    MeanReversion(int moving, double threshold, int position);
    Signal analyze(const MarketData &currentTick) override;
};

#endif