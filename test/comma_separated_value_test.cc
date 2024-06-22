#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "CommaSeparatedValue.h"
#include "DataFrame.h"

TEST(CommaSeparatedValueTest, ConstructWithFile)
{
    EXPECT_NO_THROW({
        std::vector<std::string> columns;
        columns.push_back("description");
        columns.push_back("industry");
        columns.push_back("level");
        columns.push_back("size");
        columns.push_back("line_code");
        columns.push_back("value");
        std::string dataDirectory(DATA_DIRECTORY);
        CommaSeparatedValue csv(dataDirectory + "/test1.csv");
        if (csv.df->getColumns() == columns)
        {
            SUCCEED();
        }
        else
        {
            ADD_FAILURE() << "columns of loaded test1.csv file is not correct";
        }
    });

    EXPECT_THROW({ 
        std::string dataDirectory(DATA_DIRECTORY);
        CommaSeparatedValue csv(dataDirectory + "/test1.txt"); }, std::runtime_error) << "constructor should throw runtime_error exception when given file is not csv file";

    EXPECT_THROW({ 
        std::string dataDirectory(DATA_DIRECTORY);
        CommaSeparatedValue csv(dataDirectory + "/test12456789.csv"); }, std::runtime_error) << "constructor should throw runtime_error exception when given file is not exists";
}

TEST(CommaSeparatedValueTest, ConstructWithDataFrame)
{
    std::vector<std::string> columns{"C1", "C2", "C3"};
    std::vector<std::vector<std::string>> data{
        {"R11", "R12", "R13"},
        {"R21", "R22", "R23"},
        {"R31", "R32", "R33"},
        {"R41", "R42", "R43"},
        {"R51", "R52", "R53"},
        {"R61", "R62", "R63"},
        {"R71", "R72", "R73"}};
    DataFrame df(columns, data);
    DataFrame emptyDf;

    EXPECT_NO_THROW({
        CommaSeparatedValue csv(df);
        if (csv.df->getColumns() == columns)
        {
            SUCCEED();
        }
        else
        {
            ADD_FAILURE() << "csv does not created correctly out of dataFrame";
        }
    });
}