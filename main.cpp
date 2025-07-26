#include "include/parser.h"
#include "include/strategies/meanReversion.h"
#include "orderBook.h"
#include <sstream>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./limitOrderBook <strategy> <ticker>" << "\n";
        exit(1);
    }

    Parser parser;
    OrderBook orderBook;
    std::stringstream s;
    std::string strategyName = argv[1];
    std::string ticker = argv[2];

    s << "data/intraday_1min_" << ticker << ".csv";
    std::string filename = s.str();

    auto marketData = parser.loadData(filename);

    Strategy *strategy = nullptr;

    if (strategyName == "MeanReversion")
    {
        int movingAverage, positionQuantity;
        double deviationThreshold;

        std::cout << "Enter moving-day average (between 20 and 50): " << "\n";
        std::cin >> movingAverage;

        std::cout << "Enter price deviation threshold (e.g. 1%, 2%, 5%...)" << "\n";
        std::cin >> deviationThreshold;
        deviationThreshold /= 100;

        std::cout << "Enter the quantity of shares you want for this position (10, 20, 100, 300...): " << "\n";
        std::cin >> positionQuantity;

        strategy = new MeanReversion(movingAverage, deviationThreshold, positionQuantity);
    }
    else
    {
        std::cerr << "Unknown strategy, pick from: MeanReversion, Spread, RSI";
    }

    int totalTrades = 0;
    for (const auto &tick : marketData)
    {
        Signal signal = strategy->analyze(tick);

        if (signal != HOLD)
        {
            Order order = strategy->generateOrder(signal, tick);
            orderBook.addOrder(order);
            totalTrades++;
        }
    }
    orderBook.displayBook();
    delete strategy;

    std::cout << "Backtest complete! Total trades: " << totalTrades << "\n";
    return 0;
}