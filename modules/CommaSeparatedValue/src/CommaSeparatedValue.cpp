#include "CommaSeparatedValue.h"

CommaSeparatedValue::CommaSeparatedValue(std::string csvFilePath)
{
    std::vector<std::string> columns;
    std::vector<std::vector<std::string>> data;
    std::string line;
    bool firstRow = true;
    size_t columnsSize;

    if (!std::filesystem::exists(csvFilePath))
    {
        throw std::runtime_error("\"" + csvFilePath + "\" does not exists!");
    }
    std::filesystem::path filePath = csvFilePath;
    if (filePath.extension() != ".csv")
    {
        throw std::runtime_error("\"" + csvFilePath + "\" is not a csv file!");
    }

    std::ifstream file(csvFilePath);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (firstRow)
            {
                columns = this->splitStringByComma(line);
                columnsSize = columns.size();
                firstRow = false;
            }
            else
            {
                auto newLine = this->splitStringByComma(line);
                if (newLine.size() != columnsSize)
                {
                    throw std::out_of_range("bad csv file. line " + std::to_string(data.size()) + " has " + std::to_string(newLine.size()) + " while we have " + std::to_string(columnsSize) + " columns.");
                }
                data.push_back(this->splitStringByComma(line));
            }
        }
        file.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file: " + csvFilePath);
    }
    this->df.reset(new DataFrame(columns, data));
}

CommaSeparatedValue::CommaSeparatedValue(DataFrame df)
{
    if (!df.empty())
    {
        this->df.reset(new DataFrame(df));
    }
    else
    {
        throw std::runtime_error("provided Dataframe is empty. CSV class cannot be created");
    }
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

void CommaSeparatedValue::save(std::string path)
{
    std::ofstream outputFile(path);
    if (outputFile.is_open())
    {
        std::string headerLine;
        for (const auto header : this->df->getColumns())
        {
            if (header.find(",") != std::string::npos)
            {
                headerLine += "\"" + header + "\"";
            }
            else
            {
                headerLine += header;
            }
            headerLine += ",";
        }
        headerLine.pop_back();
        headerLine += "\n";
        outputFile << headerLine;

        for (const auto row : this->df->getData())
        {
            std::string line;
            for (const auto cell : row)
            {
                if (cell.find(",") != std::string::npos)
                {
                    line += "\"" + cell + "\"";
                }
                else
                {
                    line += cell;
                }
                line += ",";
            }
            line.pop_back();
            line += "\n";
            outputFile << line;
        }
    }
    else
    {
        throw std::runtime_error("can not save csv file because \"" + path + "\" cannot be created!");
    }
}