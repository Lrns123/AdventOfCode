#include <iostream>
#include <string>

std::string lookAndSay(const std::string &input)
{
    std::string ret;
    ret.reserve(input.size() << 1);

    char currentCh = input[0];
    size_t count = 0;  // Intentionally start at zero to stop the first character being counted twice.

    for (char ch : input)
    {
        if (ch != currentCh)
        {
            ret += static_cast<char>('0' + count);  // Wrapped in a cast to suppress narrowing conversion warning.
            ret += currentCh;

            currentCh = ch;
            count = 1;
        }
        else
            ++count;
    }

    ret += static_cast<char>('0' + count);
    ret += currentCh;

    return ret;
}

int main(int, char **)
{
    std::string input;
    std::cin >> input;

    for (size_t i = 0; i != 40; ++i)
        input = lookAndSay(input);

    std::cout << "Length of result after 40 iterations: " << input.length() << std::endl;

    for (size_t i = 0; i != 10; ++i)
        input = lookAndSay(input);

    std::cout << "Length of result after 50 iterations: " << input.length() << std::endl;
}
