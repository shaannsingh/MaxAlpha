#ifndef RSI_H
#define RSI_H

#include <iostream>
#include "strategy.h"

class RelativeStrengthIndicator : public Strategy
{
protected:
    double level;

public:
    RelativeStrengthIndicator(double relativeStrength);
    Signal analyze(const MarketData &tick) override;
};

#endif