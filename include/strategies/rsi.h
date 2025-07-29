#ifndef RSI_H
#define RSI_H

#include <iostream>
#include "strategy.h"

class RelativeStrengthIndicator : public Strategy
{
protected:
    double level;
    std::vector<double> gains;
    std::vector<double> losses;

public:
    RelativeStrengthIndicator(int position);
    Signal analyze(const MarketData &currentTick) override;
};

#endif