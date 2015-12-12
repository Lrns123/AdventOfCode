#include <iostream>
#include "json/json.h"

unsigned countSum(const Json::Value &value, bool skipRed)
{
    if (value.isInt())
        return value.asInt();

    if (skipRed && value.isObject())
        for (const auto &entry : value)
            if (entry == "red")
                return 0;

    unsigned sum = 0;
    for (const auto &entry : value)
        sum += countSum(entry, skipRed);

    return sum;
}

int main(int, char **)
{
    Json::Value root;
    std::cin >> root;

    std::cout << "The sum of all numbers is: " << countSum(root, false) << std::endl;
    std::cout << "The sum of all numbers excluding everything red is: " << countSum(root, true) << std::endl;
}
