#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "DataFrame.h"

class CommaSeparatedValue
{
public:
    std::unique_ptr<DataFrame> df;
    CommaSeparatedValue(std::string csvFilePath);

private:
    std::vector<std::string> splitStringByComma(const std::string &str);
};