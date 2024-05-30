#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

class DataFrame
{
public:
    DataFrame(std::vector<std::string> columns, std::vector<std::vector<std::string>> data);
    friend std::ostream &operator<<(std::ostream &os, const DataFrame &df);
    DataFrame head(uint32_t numberOfHead);
    DataFrame tail(uint32_t numberOfTail);
    bool empty();
    bool changeColumn(std::string oldColumnName, std::string newColumnName);
    bool changeColumn(int index, std::string newColumnName);
    bool changeAllColumns(std::vector<std::string> newColumns);
    std::vector<std::string> getRow(int index);
    std::vector<std::string> getColumns();
    std::vector<std::vector<std::string>> getData();

private:
    std::vector<std::vector<std::string>> data;
    std::vector<std::string> columns;
};