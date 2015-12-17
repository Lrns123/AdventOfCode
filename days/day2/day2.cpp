#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

class Package
{
    std::vector<size_t> sides;

    static std::vector<size_t> parse(std::string input)
    {
        replace(input.begin(), input.end(), 'x', ' ');
        std::istringstream ss(input);
        std::vector<size_t> ret(std::istream_iterator<size_t>(ss), {});
        sort(ret.begin(), ret.end());
        return ret;
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