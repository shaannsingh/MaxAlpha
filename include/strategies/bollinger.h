#ifndef BOLLINGER_H
#define BOLLINGER_H

#include <iostream>
#include "strategy.h"

class Bollinger : public Strategy
{
protected:
    double deviationMultiplier;
    double upperBand;
    double lowerBand;
    double standardDeviation(std::vector<MarketData> &data);

public:
    Bollinger(double multiplier, int position);
    Signal analyze(const MarketData &currentTick) override;
};

#endif