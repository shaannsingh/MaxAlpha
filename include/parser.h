#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct MarketData
{
    std::string timestamp;
    double open;
    double high;
    double low;
    double close;
    int volume;
};

class Parser
{
private:
    std::vector<MarketData> marketData;

public:
    Parser();
    std::vector<MarketData> loadData(const std::string &data);
};

#endif