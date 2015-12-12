#include <iostream>
#include "json/json.h"

int countSum(const Json::Value &value, bool skipRed)
{
    if (value.isInt())
    {
        return value.asInt();
    }

    if (skipRed && value.isObject())
    {
        for (auto it = value.begin(), eit = value.end(); it != eit; ++it)
            if (*it == "red")
                return 0;
    }

    int sum = 0;
    for (auto it = value.begin(), eit = value.end(); it != eit; ++it)
        sum += countSum(*it, skipRed);

    return sum;
}

int main(int, char **)
{
    Json::Value root;
    std::cin >> root;

    std::cout << "The sum of all numbers is: " << countSum(root, false) << std::endl;
    std::cout << "The sum of all numbers excluding everything red is: " << countSum(root, true) << std::endl;
}
