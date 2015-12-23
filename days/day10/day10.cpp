#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void lookAndSay(std::vector<char> &input)
{
    std::vector<char> ret;
    ret.reserve(input.size() << 1);

    char currentCh = input.front();
    char count = 0;  // Intentionally start at zero to stop the first character being counted twice.

    for (char ch : input)
    {
        if (ch != currentCh)
        {
            ret.emplace_back(count); 
            ret.emplace_back(currentCh);

            currentCh = ch;
            count = 1;
        }
        else
            ++count;
    }

    ret.emplace_back(count);
    ret.emplace_back(currentCh);

    swap(input, ret);
}

int main(int, char **)
{
    std::string input;
    std::cin >> input;
    
    std::vector<char> inputVec(input.size());
    std::transform(input.begin(), input.end(), inputVec.begin(), [](char ch) { return ch - '0'; });

    for (size_t i = 0; i != 40; ++i)
        lookAndSay(inputVec);

    std::cout << "Length of result after 40 iterations: " << inputVec.size() << std::endl;

    for (size_t i = 0; i != 10; ++i)
        lookAndSay(inputVec);

    std::cout << "Length of result after 50 iterations: " << inputVec.size() << std::endl;
}
