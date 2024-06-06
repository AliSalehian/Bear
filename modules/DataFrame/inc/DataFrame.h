#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class DataFrame
{
public:
    DataFrame(std::vector<std::string> columns, std::vector<std::vector<std::string>> data);
    friend std::ostream &operator<<(std::ostream &os, const DataFrame &df);
    bool operator==(DataFrame &df);
    DataFrame head(uint32_t numberOfHead) const;
    DataFrame tail(uint32_t numberOfTail) const;
    bool empty() const;
    bool changeColumn(std::string oldColumnName, std::string newColumnName);
    void changeColumn(int index, std::string newColumnName);
    void changeAllColumns(std::vector<std::string> newColumns);
    std::vector<std::string> getRow(int index) const;
    std::vector<std::string> getColumns() const;
    std::vector<std::vector<std::string>> getData() const;

private:
    std::vector<std::vector<std::string>> data;
    std::vector<std::string> columns;
};