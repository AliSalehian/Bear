#include <iostream>
#include "DataFrame.h"

int main(int, char **)
{
    std::vector<std::string> column{"A1", "A2", "A3"};
    std::vector<std::vector<std::string>> data{
        {"Foosd1", "Fooasdasdasd2", "Foasdao3"},
        {"Boasdasdao1", "Boo2", "Boo31233123"},
        {"Doasdaso1", "Doo2asdasdasdasd", "Doo3"},
        {"1", "123", "123"},
        {"Doo1", "Doo2", "Doo3"}};
    DataFrame df(column, data);
    std::cout << df << std::endl;
    std::cout << "***************************************************" << std::endl;
    if (df.changeColumn(0, "AAAAAAAAAAAAAAAAA1"))
        std::cout << df.head(2) << std::endl;
    else
        std::cout << "failed to change columns via index" << std::endl;
    std::cout << "***************************************************" << std::endl;
    if(df.changeColumn("AAAAAAAAAAAAAAAAA1", "AA1"))
        std::cout << df.tail(2) << std::endl;
    else
        std::cout << "failed to change coulmns via old name" << std::endl;
    std::cout << "***************************************************" << std::endl;
    std::vector<std::string> newColumns{"A3", "A1", "A2"};
    if(df.changeAllColumns(newColumns))
        std::cout << df.tail(3) << std::endl;
    else    
        std::cout << "failed to change all columns" << std::endl;
}
