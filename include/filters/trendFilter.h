#ifndef TRENDFILTER_H
#define TRENDFILTER_H

#include <iostream>
#include <string>
#include <vector>
#include "order.h"
#include "portfolio.h"
#include <parser.h>

class TrendFilter
{
protected:
    std::vector<MarketData> data;
};

#endif