#include "CommaSeparatedValue.h"

CommaSeparatedValue::CommaSeparatedValue(std::string csvFilePath)
{
    std::vector<std::string> columns;
    std::vector<std::vector<std::string>> data;
    std::string line;
    bool firstRow = true;
    std::ifstream file(csvFilePath);

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (firstRow)
            {
                columns = this->splitStringByComma(line);
                firstRow = false;
            }
            else
            {
                data.push_back(this->splitStringByComma(line));
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << csvFilePath << std::endl;
    }
    this->df.reset(new DataFrame(columns, data));
}

std::vector<std::string> CommaSeparatedValue::splitStringByComma(const std::string &str)
{
    std::vector<std::string> result;
    std::string current;
    bool inQuotes = false;

    for (char ch : str)
    {
        if (ch == '"')
        {
            inQuotes = !inQuotes; // Toggle the inQuotes flag
        }
        else if (ch == ',' && !inQuotes)
        {
            boost::algorithm::trim(current);
            result.push_back(current); // Add the current string to the result
            current.clear();           // Reset the current string
        }
        else
        {
            current += ch; // Add the character to the current string
        }
    }
    boost::algorithm::trim(current);
    result.push_back(current); // Add the last segment
    return result;
}