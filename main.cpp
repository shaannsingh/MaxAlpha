#include "include/parser.h"
#include "include/strategies/meanReversion.h"
#include "include/strategies/rsi.h"
#include "orderBook.h"
#include <sstream>
#include <string>

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        std::cerr << "Usage: ./limitOrderBook <strategy> <ticker> <quantity> <window>" << "\n";
        exit(1);
    }

    Parser parser;
    OrderBook orderBook;
    std::stringstream s;
    std::string strategyName = argv[1];
    std::string ticker = argv[2];
    std::string quantity = argv[3];
    int positionQuantity = stoi(quantity);
    std::string window = argv[4];
    int analysisWindow = stoi(window);

    s << "data/daily_" << ticker << ".csv";
    std::string filename = s.str();

    auto marketData = parser.loadData(filename);

    Strategy *strategy = nullptr;

    if (strategyName == "MeanReversion")
    {
        int movingAverage;
        double deviationThreshold;

        std::cout << "Enter moving-day average (between 20 and 50): " << "\n";
        std::cin >> movingAverage;

        std::cout << "Enter price deviation threshold (e.g. 1%, 2%, 5%...)" << "\n";
        std::cin >> deviationThreshold;

        strategy = new MeanReversion(movingAverage, deviationThreshold, positionQuantity);
    }
    else if (strategyName == "RSI")
    {

        strategy = new RelativeStrengthIndicator(positionQuantity);
    }
    else
    {
        std::cerr << "Unknown strategy, pick from: MeanReversion, Spread, RSI";
    }

    int totalTrades = 0;
    int displayedTrades = 0;

    for (int i = analysisWindow - 1; i >= 0; i--)
    {
        {
            Signal signal = strategy->analyze(marketData[i]);

            if (signal != HOLD)
            {
                Order order = strategy->generateOrder(signal, marketData[i]);
                orderBook.addOrder(order);
                totalTrades++;
            }
        }
    }

    orderBook.displayBook();
    delete strategy;

    std::cout << "Backtest complete! Total trades: " << totalTrades << "\n";
    return 0;
}