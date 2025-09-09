#include <iostream>
#include <strategies/rsi.h>
#include <numeric>
#include <deque>

RelativeStrengthIndicator::RelativeStrengthIndicator(int position) : Strategy(position) {};

Signal RelativeStrengthIndicator::analyze(const MarketData &currentTick)
{
    std::deque<double> prices;
    prices.push_back(currentTick.close);

    if (prices.size() < 15)
        return HOLD;
    if (prices.size() > 15)
        prices.pop_front();

    std::vector<double> gains, losses;
    for (size_t i = 1; i < prices.size(); i++)
    {
        double change = prices[i] - prices[i - 1];
        if (change > 0)
        {
            gains.push_back(change);
            losses.push_back(0.0);
        }
        else
        {
            losses.push_back(-change);
            gains.push_back(0.0);
        }
    }

    if (gains.empty() || losses.empty())
        return HOLD;

    double avgGain = (std::accumulate(gains.begin(), gains.end(), 0.0) / gains.size());
    double avgLoss = (std::accumulate(losses.begin(), losses.end(), 0.0) / losses.size());

    if (avgLoss == 0.0)
        return SELL;
    if (avgGain == 0.0)
        return BUY;

    double relativeStrength = avgGain / avgLoss;
    double relativeStrengthIndex = 100 - (100 / (1 + relativeStrength));

    if (relativeStrengthIndex > 70)
        return SELL;
    else if (relativeStrengthIndex < 30)
        return BUY;
    else
        return HOLD;
}