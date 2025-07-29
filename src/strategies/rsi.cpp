#include <iostream>
#include <strategies/rsi.h>
#include <numeric>

RelativeStrengthIndicator::RelativeStrengthIndicator(int position) : Strategy(position) {};

Signal RelativeStrengthIndicator::analyze(const MarketData &currentTick)
{
    gains.clear();
    losses.clear();

    data.push_back(currentTick);
    if (data.size() < 15)
        return HOLD;

    for (int i = (int)(data.size() - 14); (int)i < (int)data.size() - 1; i++)
    {
        double change = data[i + 1].close - data[i].close;
        if (change > 0)
        {
            gains.push_back(change);
            losses.push_back(0);
        }
        else
        {
            losses.push_back(-change);
            gains.push_back(0);
        }
    }

    if (gains.empty() || losses.empty())
    {
        std::cerr << "Error: data not read or empty." << "\n";
    }

    double avgGain = (std::accumulate(gains.begin(), gains.end(), 0.0) / gains.size());
    double avgLoss = (std::accumulate(losses.begin(), losses.end(), 0.0) / losses.size());

    if (avgLoss == 0.0)
    {
        return SELL;
    }
    if (avgGain == 0.0)
    {
        return BUY;
    }

    double relativeStrength = avgGain / avgLoss;

    double relativeStrengthIndex = 100 - (100 / (1 + relativeStrength));

    if (relativeStrengthIndex > 70)
        return SELL; // Overbought
    else if (relativeStrengthIndex < 30)
        return BUY; // Oversold
    else
        return HOLD; // Safe
}