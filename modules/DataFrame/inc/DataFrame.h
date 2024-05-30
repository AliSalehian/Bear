#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

class DataFrame
{
public:
    DataFrame(std::vector<std::string> columns, std::vector<std::vector<std::string>> data);
    friend std::ostream &operator<<(std::ostream &os, const DataFrame &df);
    DataFrame head(uint32_t numberOfHead);
    DataFrame tail(uint32_t numberOfTail);
    bool empty();

private:
    std::vector<std::vector<std::string>> data;
    std::vector<std::string> columns;
};