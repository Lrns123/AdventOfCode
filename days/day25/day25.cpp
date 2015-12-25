#include <iostream>
#include <regex>

bool getInput(unsigned &row, unsigned &col)
{
    static const std::regex inputRegex("To continue, please consult the code grid in the manual.  Enter the code at row (\\d+), column (\\d+).");
    std::string line;
    std::smatch match;
    getline(std::cin, line);

    if (regex_match(line, match, inputRegex))
    {
        row = stoul(match[1]), col = stoul(match[2]);
        return true;
    }

    return false;
}

int main(int, char **)
{
    unsigned row, col;
    if (!getInput(row, col))
    {
        std::cout << "Could not parse input." << std::endl;
        return 1;
    }

    unsigned long long index = 0;
    for (unsigned i = col + row - 1; i > 0; --i)
        index += i;
    index -= row - 1;


    unsigned long long code = 20151125;
    while (--index)
        code = code * 252533 % 33554393;

    std::cout << "Code: " << code << std::endl;
}
