#include "DataFrame.h"

DataFrame::DataFrame(std::vector<std::string> columns, std::vector<std::vector<std::string>> data) : data(data), columns(columns)
{
}

DataFrame DataFrame::head(uint32_t numberOfHead) const
{
    if (numberOfHead >= this->data.size() || numberOfHead <= 0)
    {
        throw std::out_of_range("Requested index is out of range. Requested index: " + std::to_string(numberOfHead) + ", number of rows: " + std::to_string(this->data.size()));
    }
    std::vector<std::vector<std::string>> newData(this->data.begin(), this->data.begin() + numberOfHead);
    DataFrame result(this->columns, newData);
    return result;
}

DataFrame DataFrame::tail(uint32_t numberOfTail) const
{
    if (numberOfTail >= this->data.size() || numberOfTail <= 0)
    {
        throw std::out_of_range("Requested index is out of range. Requested index: " + std::to_string(numberOfTail) + ", number of rows: " + std::to_string(this->data.size()));
    }
    std::vector<std::vector<std::string>> newData(this->data.end() - numberOfTail, this->data.end());
    DataFrame result(this->columns, newData);
    return result;
}

bool DataFrame::empty() const
{
    return this->data.empty();
}

void DataFrame::changeColumn(std::string oldColumnName, std::string newColumnName)
{
    auto position = std::find(this->columns.begin(), this->columns.end(), oldColumnName);
    if (position == this->columns.end())
    {
        std::string columnsString = "[";
        for (const auto column : this->columns)
        {
            columnsString += "'" + column + "', ";
        }
        columnsString.pop_back();
        columnsString.pop_back();
        columnsString += "]";
        throw std::invalid_argument("You want to change '" + oldColumnName + "' column, but it's not exist in columns of DataFrame. It has these columns: " + columnsString);
    }
    this->columns[std::distance(this->columns.begin(), position)] = newColumnName;
}

void DataFrame::changeColumn(int index, std::string newColumnName)
{
    if (index >= this->columns.size() || index < 0)
    {
        throw std::out_of_range("Requested column by index is out of range. Requested index: " + std::to_string(index) + ", number of columns: " + std::to_string(this->columns.size()));
    }
    this->columns[index] = newColumnName;
}

void DataFrame::changeAllColumns(std::vector<std::string> newColumns)
{
    if (newColumns.size() != this->columns.size())
    {
        throw std::out_of_range("Size of new columns are not equal with existing columns. New columns size: " + std::to_string(newColumns.size()) + ", existing columns size: " + std::to_string(this->columns.size()));
    }
    this->columns = newColumns;
}

std::vector<std::string> DataFrame::getRow(int index) const
{
    if (index >= this->data.size() || index < 0)
    {
        throw std::out_of_range("Requested row by index is out of range. Requested index: " + std::to_string(index) + ", number of rows: " + std::to_string(this->data.size()));
    }
    return this->data[index];
}

std::vector<std::string> DataFrame::getColumn(int index) const
{
    if (index >= this->columns.size() || index < 0)
    {
        throw std::out_of_range("Requested column by index is out of range. Requested index: " + std::to_string(index) + ", number of columns: " + std::to_string(this->columns.size()));
    }
    std::vector<std::string> result;
    for (int i = 0; i < this->data.size(); i++)
    {
        for (int j = 0; j < this->data[0].size(); j++)
        {
            if (j == index)
            {
                result.emplace_back(data[i][j]);
            }
        }
    }
    return result;
}

std::vector<std::string> DataFrame::getColumn(std::string columnName) const
{
    auto position = std::find(this->columns.begin(), this->columns.end(), columnName);
    if (position == this->columns.end())
    {
        std::string columnsString = "[";
        for (const auto column : this->columns)
        {
            columnsString += "'" + column + "', ";
        }
        columnsString.pop_back();
        columnsString.pop_back();
        columnsString += "]";
        throw std::invalid_argument("You want to get '" + columnName + "' column, but it's not exist in columns of DataFrame. It has these columns: " + columnsString);
    }
    int index = position - this->columns.begin();
    return this->getColumn(index);
}

std::vector<std::string> DataFrame::getColumns() const
{
    return this->columns;
}

std::vector<std::vector<std::string>> DataFrame::getData() const
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

bool DataFrame::operator==(DataFrame &df)
{
    if (this->columns.size() == df.columns.size() && this->data.size() == df.data.size())
    {
        for (int i = 0; i < this->columns.size(); ++i)
        {
            if (this->columns[i] != df.columns[i])
            {
                return false;
            }
        }

        for (int i = 0; i < this->data.size(); ++i)
        {
            for (int j = 0; j < this->data[0].size(); ++j)
            {
                if (this->data[i][j] != df.data[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}