#include "strategies/strategy.h"

Strategy::Strategy(int position) : positionQuantity(position) {};

int Strategy::orderCount = 0;

Order Strategy::generateOrder(Signal signal, const MarketData &currentTick)
{
    orderCount++;
    char side = (signal == BUY ? 'B' : 'S');
    double price = currentTick.close;
    int quantity = positionQuantity;
    long timestamp = currentTick.timestamp;
    int id = orderCount;
    return Order(id, side, price, quantity, timestamp);
}

double Strategy::findMovingAverage(int movingAverageWindow)
{
    double sum = 0.0;

    for (size_t i = (data.size() - movingAverageWindow); i < data.size(); i++)
    {
        sum += data[i].close;
    }

    return sum / movingAverageWindow;
}