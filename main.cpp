#include "include/parser.h"
#include "include/strategies/meanReversion.h"
#include "include/strategies/rsi.h"
#include "include/strategies/bollinger.h"
#include "orderBook.h"
#include "portfolio.h"
#include <sstream>
#include <string>

int main(int argc, char **argv)
{
    if (argc != 6)
    {
        std::cerr << "Usage: ./limitOrderBook <strategy> <ticker> <cash> <quantity> <window>" << "\n";
        exit(1);
    }

    Parser parser;
    OrderBook orderBook;
    std::stringstream s;
    std::string strategyName = argv[1];
    std::string ticker = argv[2];
    std::string cash = argv[3];
    double capital = std::stod(cash);
    std::string quantity = argv[4];
    int positionQuantity = stoi(quantity);
    std::string window = argv[5];
    int analysisWindow = stoi(window);

    Portfolio portfolio(capital);

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
    else if (strategyName == "Bollinger")
    {
        double deviationMultiplier;

        std::cout << "Enter your deviation multiplier - 0.5 (tight), 1.0 (reasonable), 2.0 (loose), 5.0 (crazy): " << "\n";
        std::cin >> deviationMultiplier;
        strategy = new Bollinger(deviationMultiplier, positionQuantity);
    }
    else
    {
        std::cerr << "Unknown strategy, pick from: MeanReversion, Spread, RSI";
    }

    int totalTrades = 0;
    int displayedTrades = 0;
    std::vector<double> dailyValues;
    std::vector<double> dailyReturns;

    for (int i = analysisWindow - 1; i >= 0; i--)
    {
        Signal signal = strategy->analyze(marketData[i]);

        if (signal != HOLD)
        {
            Order order = strategy->generateOrder(signal, marketData[i]);
            if (order.getOrderSide() == 'S' && portfolio.getPortfolioShares() == 0)
                continue;
            if (portfolio.sufficientFunds(order))
            {
                orderBook.addOrder(order);
                portfolio.process(order);
                totalTrades++;
            }
            else
            {
                std::cout << "Order for " << order.getOrderSide() << " " << order.getOrderQuantity() << " shares of " << ticker << " rejected due to insufficient funds." << "\n";
            }
        }

        double todaysValue = portfolio.getPortfolioValue(marketData[i].close);
        dailyValues.push_back(todaysValue);
    }

    for (int i = 1; i < dailyValues.size(); i++)
    {
        double returnValue = (dailyValues[i] - dailyValues[i - 1]) / dailyValues[i - 1];
        if (returnValue == 0)
            continue;
        dailyReturns.push_back(returnValue);
    }

    double sharpe = portfolio.sharpeRatio((0.02 / 252), dailyReturns, marketData[0].close);
    orderBook.displayBook();
    delete strategy;

    std::cout << "=== PERFORMANCE SUMMARY ===" << std::endl;
    std::cout << "Starting capital: $" << capital << std::endl;
    std::cout << "Ending value: $" << portfolio.getPortfolioValue(marketData[0].close) << std::endl;
    std::cout << "Total return: " << ((portfolio.getPortfolioValue(marketData[0].close) - capital) / capital) * 100 << "%" << std::endl;
    std::cout << "P&L: $" << portfolio.calculatePnL() << std::endl;
    std::cout << "Total trades: " << totalTrades << std::endl;
    std::cout << "Sharpe ratio: " << sharpe << std::endl;
    return 0;
}