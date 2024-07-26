#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "DataFrame.h"

class DataFrameTest : public testing::Test
{
protected:
    DataFrameTest()
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
        std::vector<std::vector<std::string>> topFive{
            {"R11", "R12", "R13"},
            {"R21", "R22", "R23"},
            {"R31", "R32", "R33"},
            {"R41", "R42", "R43"},
            {"R51", "R52", "R53"}};
        std::vector<std::vector<std::string>> topThree{
            {"R11", "R12", "R13"},
            {"R21", "R22", "R23"},
            {"R31", "R32", "R33"}};

        std::vector<std::vector<std::string>> lastFive{
            {"R31", "R32", "R33"},
            {"R41", "R42", "R43"},
            {"R51", "R52", "R53"},
            {"R61", "R62", "R63"},
            {"R71", "R72", "R73"}};
        std::vector<std::vector<std::string>> lastThree{
            {"R51", "R52", "R53"},
            {"R61", "R62", "R63"},
            {"R71", "R72", "R73"}};

        this->df = DataFrame(columns, data);
        this->topFiveDf = DataFrame(columns, topFive);
        this->topThreeDf = DataFrame(columns, topThree);
        this->lastFiveDf = DataFrame(columns, lastFive);
        this->lastThreeDf = DataFrame(columns, lastThree);
    }

    DataFrame df, topFiveDf, topThreeDf, lastFiveDf, lastThreeDf;
};

TEST_F(DataFrameTest, HeadMethod)
{
    auto topFiveDfGenerated = df.head(5);
    auto topThreeDfGenerated = df.head(3);
    if (topFiveDf == topFiveDfGenerated)
    {
        SUCCEED();
    }
    else
    {
        ADD_FAILURE() << "top five generated is not correct";
    }

    if (topThreeDf == topThreeDfGenerated)
    {
        SUCCEED();
    }
    else
    {
        ADD_FAILURE() << "top three generated is not correct";
    }

    if (!(topFiveDf == topThreeDfGenerated))
    {
        SUCCEED();
    }
    else
    {
        ADD_FAILURE() << "top five generated is not correct";
    }

    EXPECT_THROW({ auto zeroIndex = df.head(0); }, std::out_of_range) << "head method should throw out_of_range exception when given argument is 0";

    EXPECT_THROW({ auto zeroIndex = df.head(-12); }, std::out_of_range) << "head method should throw out_of_range exception when given argument is negative";

    EXPECT_THROW({ auto zeroIndex = df.head(8); }, std::out_of_range) << "head method should throw out_of_range exception when given argument is more than number of rows";
}

TEST_F(DataFrameTest, TailMethod)
{
    auto lastFiveDfGenerated = df.tail(5);
    auto lastThreeDfGenerated = df.tail(3);

    if (lastFiveDf == lastFiveDfGenerated)
    {
        SUCCEED();
    }
    else
    {
        ADD_FAILURE() << "top five generated is not correct";
    }

    if (lastThreeDf == lastThreeDfGenerated)
    {
        SUCCEED();
    }
    else
    {
        ADD_FAILURE() << "top three generated is not correct";
    }

    if (!(lastFiveDf == lastThreeDfGenerated))
    {
        SUCCEED();
    }
    else
    {
        ADD_FAILURE() << "top five generated is not correct";
    }

    EXPECT_THROW({ auto zeroIndex = df.tail(0); }, std::out_of_range) << "tail method should throw out_of_range exception when given argument is 0";

    EXPECT_THROW({ auto zeroIndex = df.tail(-12); }, std::out_of_range) << "tail method should throw out_of_range exception when given argument is negative";

    EXPECT_THROW({ auto zeroIndex = df.tail(8); }, std::out_of_range) << "tail method should throw out_of_range exception when given argument is more than number of rows";
}

TEST_F(DataFrameTest, ChangeColumnMethods)
{
    std::vector<std::string> newColumns{"TEST1", "TEST2", "TEST3"};
    df.changeColumn("C1", "CC1");
    if (df.getColumns() == std::vector<std::string>{"CC1", "C2", "C3"})
    {
        SUCCEED();
    }
    else
    {
        FAIL() << "changeColumn method which gets 2 string as input failed!";
    }

    EXPECT_THROW({ df.changeColumn("TEST", "TEST!23"); }, std::invalid_argument) << "changeColumn method should throw invalid_argument exception when given old column name doesn't exist in columns list";

    df.changeColumn(0, "C1");
    if (df.getColumns() == std::vector<std::string>{"C1", "C2", "C3"})
    {
        SUCCEED();
    }
    else
    {
        FAIL() << "changeColumn method which gets one integer and one string as input failed!";
    }

    EXPECT_THROW({ df.changeColumn(-1, "TEST!23"); }, std::out_of_range) << "changeColumn method should throw out_of_range exception when given index is negative";
    EXPECT_THROW({ df.changeColumn(3, "TEST!23"); }, std::out_of_range) << "changeColumn method should throw out_of_range exception when given index is more than number of columns";

    df.changeAllColumns(newColumns);
    if (df.getColumns() == std::vector<std::string>{"TEST1", "TEST2", "TEST3"})
    {
        SUCCEED();
    }
    else
    {
        FAIL() << "changeAllColumns method failed!";
    }

    newColumns.emplace_back("TEST4");
    EXPECT_THROW({ df.changeAllColumns(newColumns); }, std::out_of_range) << "changeAllColumns method should throw out_of_range exception when given vector size is not equal with existing column vector";
}

TEST_F(DataFrameTest, GetRowMethod)
{
    if (df.getRow(0) == std::vector<std::string>{"R11", "R12", "R13"})
    {
        SUCCEED();
    }
    else
    {
        FAIL() << "failed to get row correctly!";
    }

    if (df.getRow(df.getData().size() - 1) == std::vector<std::string>{"R71", "R72", "R73"})
    {
        SUCCEED();
    }
    else
    {
        FAIL() << "failed to get row correctly!";
    }

    EXPECT_THROW({ auto row = df.getRow(-1); }, std::out_of_range) << "getRow method should throw out_of_range exception when given vector is negative";
    EXPECT_THROW({ auto row = df.getRow(10); }, std::out_of_range) << "getRow method should throw out_of_range exception when given vector is more than number of rows";
}

TEST_F(DataFrameTest, GetColumnMethod)
{
    std::vector<std::string> expected{"R12", "R22", "R32", "R42", "R52", "R62", "R72"};
    if (df.getColumn("C2") == expected)
    {
        SUCCEED();
    }
    else
    {
        FAIL() << "returned column is not correct";
    }

    if (df.getColumn(1) == expected)
    {
        SUCCEED();
    }
    else
    {
        FAIL() << "returned column is not correct";
    }

    EXPECT_THROW({ auto column = df.getColumn(10); }, std::out_of_range) << "getColumn method should throw out_of_range exception when given vector is bigger than number of rows";
    EXPECT_THROW({ auto column = df.getColumn(-1); }, std::out_of_range) << "getColumn method should throw out_of_range exception when given index is negative";
    EXPECT_THROW({ auto column = df.getColumn("CCC"); }, std::invalid_argument) << "getColumn method should throw invalid_argument exception when given column name not exist";
}