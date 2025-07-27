#include "strategies/strategy.h"

Strategy::Strategy() {};

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