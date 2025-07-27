#include <iostream>
#include <strategies/rsi.h>
#include <numeric>

RelativeStrengthIndicator::RelativeStrengthIndicator(int position)
{
    this->positionQuantity = position;
};

double sum(std::vector<double> &v)
{
    double s = 0.00;
    for (int i = 0; i < v.size(); i++)
    {
        s += v[i];
    }
    return s;
}

Signal RelativeStrengthIndicator::analyze(const MarketData &currentTick)
{
    gains.clear();
    losses.clear();

    data.push_back(currentTick);
    if (data.size() < 15)
        return HOLD;

    for (int i = (int)(data.size() - 14); (int)i < data.size() - 1; i++)
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

    double relativeStrength = (std::accumulate(gains.begin(), gains.end(), 0) / gains.size()) /
                              (std::accumulate(losses.begin(), losses.end(), 0) / losses.size());
    double relativeStrengthIndex = 100 - (100 / (1 + relativeStrength));

    if (relativeStrengthIndex > 70)
        return SELL; // Overbought
    else if (relativeStrengthIndex < 30)
        return BUY; // Oversold
    else
        return HOLD; // Safe
}