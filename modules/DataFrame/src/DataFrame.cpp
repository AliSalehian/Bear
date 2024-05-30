#include "DataFrame.h"

DataFrame::DataFrame(std::vector<std::string> columns, std::vector<std::vector<std::string>> data) : data(data), columns(columns)
{
}

DataFrame DataFrame::head(uint32_t numberOfHead)
{
    std::vector<std::vector<std::string>> newData(this->data.begin(), this->data.begin() + numberOfHead);
    DataFrame result(this->columns, newData);
    return result;
}

DataFrame DataFrame::tail(uint32_t numberOfTail)
{
    std::vector<std::vector<std::string>> newData(this->data.end() - numberOfTail, this->data.end());
    DataFrame result(this->columns, newData);
    return result;
}

bool DataFrame::empty()
{
    return this->data.empty();
}

bool DataFrame::changeColumn(std::string oldColumnName, std::string newColumnName)
{
    auto position = std::find(this->columns.begin(), this->columns.end(), oldColumnName);
    if (position == this->columns.end())
    {
        return false;
    }
    this->columns[std::distance(this->columns.begin(), position)] = newColumnName;
    return true;
}

bool DataFrame::changeColumn(int index, std::string newColumnName)
{
    if (index >= this->columns.size())
    {
        return false;
    }
    this->columns[index] = newColumnName;
    return true;
}

bool DataFrame::changeAllColumns(std::vector<std::string> newColumns)
{
    if (newColumns.size() != this->columns.size())
    {
        return false;
    }
    this->columns = newColumns;
    return true;
}

std::vector<std::string> DataFrame::getColumns()
{
    return this->columns;
}

std::vector<std::vector<std::string>> DataFrame::getData()
{
    return this->data;
}

std::ostream &operator<<(std::ostream &os, const DataFrame &df)
{
    auto numberOfRows = df.data.size();
    auto numberOfcolumns = df.data[0].size();
    std::vector<int> columnWidths(numberOfcolumns, 0);
    for (int j = 0; j < numberOfcolumns; ++j)
    {
        for (int i = 0; i < numberOfRows; ++i)
        {
            int numDigits = df.data[i][j].length();
            columnWidths[j] = std::max(columnWidths[j], numDigits);
        }
    }
    for (int i = 0; i < df.columns.size(); i++)
    {
        int numDigits = df.columns[i].length();
        columnWidths[i] = std::max(columnWidths[i], numDigits);
    }

    auto generateHorizontalLine = [&](int cols, const std::vector<int> &columnWidths)
    {
        std::string result;
        for (int j = 0; j < cols; ++j)
        {
            result += "+-" + std::string(columnWidths[j], '-') + "-";
        }
        result += "+";
        return result;
    };

    os << generateHorizontalLine(numberOfcolumns, columnWidths) << std::endl;
    for (int i = 0; i < df.columns.size(); ++i)
    {
        os << "| " << df.columns[i] << std::string(columnWidths[i] - df.columns[i].length(), ' ') << " ";
    }
    os << "|" << std::endl
       << generateHorizontalLine(numberOfcolumns, columnWidths) << std::endl;
    for (int i = 0; i < numberOfRows; ++i)
    {
        for (int j = 0; j < numberOfcolumns; ++j)
        {
            os << "| " << df.data[i][j] << std::string(columnWidths[j] - df.data[i][j].length(), ' ') << " ";
        }
        os << "|" << std::endl
           << generateHorizontalLine(numberOfcolumns, columnWidths) << std::endl;
    }
    return os;
}