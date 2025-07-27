#ifndef STRATEGY_H
#define STRATEGY_H

#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
#include "order.h"

enum Signal
{
    BUY,
    SELL,
    HOLD
};

class Strategy
{
protected:
    std::vector<MarketData> data;
    static int orderCount;
    int positionQuantity;

public:
    Strategy();
    virtual ~Strategy() = default;
    virtual Signal analyze(const MarketData &newTick) = 0;
    Order generateOrder(Signal signal, const MarketData &currentTick);
};

#endif