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

std::ostream &operator<<(std::ostream &os, const DataFrame &df)
{
    auto numberOfRows = df.data.size();
    auto numberOfcolumns = df.data[0].size();
    std::cout << "number of columns: " << numberOfcolumns << std::endl;
    std::vector<int> columnWidths(numberOfcolumns, 0);
    for (int j = 0; j < numberOfcolumns; ++j)
    {
        for (int i = 0; i < numberOfRows; ++i)
        {
            int numDigits = df.data[i][j].length();
            columnWidths[j] = std::max(columnWidths[j], numDigits);
        }
        std::cout << "max size " << j << ": " << columnWidths[j] << std::endl;
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