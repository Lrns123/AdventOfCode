#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

class Package
{
    std::vector<size_t> sides;

    static std::vector<size_t> parse(std::string input)
    {
        std::vector<size_t> result;
        std::istringstream stream(input);

        std::string token;
        while (getline(stream, token, 'x'))
            result.emplace_back(stoi(token));

        std::sort(result.begin(), result.end());
        return result;
    }

public:

    explicit Package(std::string dimensions)
        : sides(parse(dimensions))
    {}

    size_t paperRequired() const
    {
        return 3 * sides[0] * sides[1] + 2 * sides[1] * sides[2] + 2 * sides[2] * sides[0];
    }

    size_t ribbonRequired() const
    {
        return sides[0] + sides[0] + sides[1] + sides[1] + (sides[0] * sides[1] * sides[2]);
    }

};

// Advent of code - Day 2
int main(int, char **)
{
    size_t paperRequried = 0;
    size_t ribbonRequired = 0;
    
    std::string line;
    while (getline(std::cin, line))
    {
        Package package(line);
        paperRequried += package.paperRequired();
        ribbonRequired += package.ribbonRequired();
    }   

    std::cout << "Paper required: " << paperRequried << " square feet." << std::endl;
    std::cout << "Ribbon required: " << ribbonRequired << " square feet." << std::endl;
}