#include <iostream>
#include <regex>

using ull = unsigned long long;
// Calculates initial * base ^ exponent % modulus
ull modexp(unsigned base, ull exponent, ull modulus, ull initial = 1)
{
    ull result = initial;
    while (exponent)
    {
        if (exponent & 1)
            result = (result * base) % modulus;
        exponent >>= 1;
        base = (base * base) % modulus;
    }

    return result;
}

int main(int, char **)
{
    static constexpr ull initial = 20151125, multiplicand = 252533, modulus = 33554393;
    static const std::regex inputRegex("To continue, please consult the code grid in the manual.  Enter the code at row (\\d+), column (\\d+).");

    std::string line;
    std::smatch match;
    getline(std::cin, line);
    if (!regex_match(line, match, inputRegex))
    {
        std::cout << "Could not parse input." << std::endl;
        return 1;
    }

    unsigned row = stoul(match[1]), col = stoul(match[2]);

    ull index = 0;
    for (unsigned i = col + row - 1; i > 0; --i)
        index += i;
    index -= row;

    std::cout << "Code: " << modexp(multiplicand, index, modulus, initial) << std::endl;
}
