#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "DataFrame.h"

TEST(DataFrameTest, HeadMethod)
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

    DataFrame df(columns, data);
    DataFrame topFiveDf(columns, topFive);
    DataFrame topThreeDf(columns, topThree);

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

    EXPECT_THROW({ auto zeroIndex = df.head(0); }, std::out_of_range);

    EXPECT_THROW({ auto zeroIndex = df.head(-12); }, std::out_of_range);

    EXPECT_THROW({ auto zeroIndex = df.head(8); }, std::out_of_range);
}

TEST(DataFrameTest, TailMethod)
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

    DataFrame df(columns, data);
    DataFrame lastFiveDf(columns, lastFive);
    DataFrame lastThreeDf(columns, lastThree);

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

    EXPECT_THROW({ auto zeroIndex = df.tail(0); }, std::out_of_range);

    EXPECT_THROW({ auto zeroIndex = df.tail(-12); }, std::out_of_range);

    EXPECT_THROW({ auto zeroIndex = df.tail(8); }, std::out_of_range);
}