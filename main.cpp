// In main.cpp
#include "include/parser.h"
#include "include/strategies/meanReversion.h"

int main()
{
    Parser parser;
    auto marketData = parser.loadData("data/intraday_1min_AAPL.csv");

    MeanReversion strategy(20, 0.02, 100);

    int totalTrades = 0;
    for (const auto &tick : marketData)
    {
        Signal signal = strategy.analyze(tick);

        if (signal != HOLD)
        {
            Order order = strategy.generateOrder(signal, tick);
            totalTrades++;

            std::cout << "TRADE #" << totalTrades << ": "
                      << (signal == BUY ? "BUY" : "SELL")
                      << " " << order.getOrderQuantity()
                      << " shares at $" << order.getOrderPrice() << std::endl;
        }
    }

    std::cout << "Backtest complete! Total trades: " << totalTrades << "\n";
    return 0;
}