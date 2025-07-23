#include <iostream>
#include "include/orderBook.h"
#include "include/parser.h"

int main()
{
    Parser parser;
    auto data = parser.loadData("data/intraday_1min_AAPL.csv");

    std::cout << "Parsed " << data.size() << " rows" << std::endl;
    if (!data.empty())
    {
        std::cout << "First entry: " << data[0].timestamp << ", $" << data[0].close << std::endl;
    }
}