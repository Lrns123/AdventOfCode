#include "instruction.hpp"
#include <sstream>
#include <algorithm>
#include <iterator>

namespace
{
    std::vector<std::string> splitTokens(std::string line, int reserve = 0)
    {
        replace(line.begin(), line.end(), ',', ' ');

        std::vector<std::string> tokens;
        if (reserve)
            tokens.reserve(reserve);

        using Iter = std::istream_iterator<std::string>;
        std::istringstream ss(line);
        copy(Iter(ss), Iter(), back_inserter(tokens));

        return tokens;
    }
}

Instruction::Instruction(const std::string& instruction)
{
    parse(instruction);
}

const Instruction& Instruction::apply(bool(& grid)[1000][1000]) const
{
    for (size_t x = topLeft.x; x <= bottomRight.x; ++x)
        for (size_t y = topLeft.y; y <= bottomRight.y; ++y)
            switch (op)
            {
                case TurnOn:
                    grid[x][y] = true;
                    break;
                case TurnOff:
                    grid[x][y] = false;
                    break;
                case Toggle:
                    grid[x][y] = !grid[x][y];
                    break;
                default:
                    break;
            }

    return *this;
}

const Instruction& Instruction::apply(size_t(& grid)[1000][1000]) const
{
    for (size_t x = topLeft.x; x <= bottomRight.x; ++x)
        for (size_t y = topLeft.y; y <= bottomRight.y; ++y)
            switch (op)
            {
                case TurnOn:
                    ++grid[x][y];
                    break;
                case TurnOff:
                    if (grid[x][y] != 0)
                        --grid[x][y];
                    break;
                case Toggle:
                    grid[x][y] += 2;
                    break;
                default:
                    break;
            }

    return *this;
}

void Instruction::parse(const std::string& instruction)
{
    auto tokens = splitTokens(instruction, 7);
    size_t currentToken = 0;

    if (tokens.size() < 6)
        throw SyntaxError();

    if (tokens[currentToken] == "turn")
    {
        if (tokens[++currentToken] == "on")
            op = TurnOn;
        else if (tokens[currentToken] == "off")
            op = TurnOff;
        else throw SyntaxError();
    }
    else if (tokens[currentToken] == "toggle")
        op = Toggle;
    else throw SyntaxError();

    topLeft.x = stoi(tokens[++currentToken]);
    topLeft.y = stoi(tokens[++currentToken]);

    if (tokens[++currentToken] != "through")
        throw SyntaxError();

    bottomRight.x = stoi(tokens[++currentToken]);
    bottomRight.y = stoi(tokens[++currentToken]);
}