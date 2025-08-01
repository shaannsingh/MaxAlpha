#include <iostream>
#include <algorithm>
#include "../include/parser.h"

Parser::Parser() {}

std::vector<MarketData> Parser::loadData(const std::string &data)
{
    std::vector<MarketData> marketData;
    std::ifstream fp(data);
    std::string line;
    bool header;

    if (fp.is_open())
    {
        header = true;
        while (std::getline(fp, line))
        {
            if (line.empty())
                continue;

            if (header)
            {
                header = false;
                continue;
            }

            std::stringstream s(line);
            std::string timeStamp, openStr, highStr, lowStr, closeStr, volumeStr;

            std::getline(s, timeStamp, ',');
            std::getline(s, openStr, ',');
            std::getline(s, highStr, ',');
            std::getline(s, lowStr, ',');
            std::getline(s, closeStr, ',');
            std::getline(s, volumeStr);
            MarketData tick;
            std::string dirtyTimeStamp = timeStamp;
            tick.timestamp = cleanTimeStamp(dirtyTimeStamp);
            tick.open = stod(openStr);
            tick.high = stod(highStr);
            tick.low = stod(lowStr);
            tick.close = stod(closeStr);
            tick.volume = stoi(volumeStr);

            marketData.push_back(tick);
        }
    }
    else
    {
        std::cerr << "Could not open file." << "\n";
        exit(2);
    }

    return marketData;
}

long Parser::cleanTimeStamp(std::string timestamp)
{
    timestamp.erase(std::remove(timestamp.begin(), timestamp.end(), ' '));
    timestamp.erase(std::remove(timestamp.begin(), timestamp.end(), '-'));
    timestamp.erase(std::remove(timestamp.begin(), timestamp.end(), ':'));
    long newTimeStamp = stol(timestamp);
    return newTimeStamp;
}