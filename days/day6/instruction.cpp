#include "instruction.hpp"
#include <sstream>

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
    std::string token;
    std::istringstream ss(instruction);

    parseOperator(ss);
    topLeft = parseCoordinate(ss);

    ss >> token;
    if (token != "through")
        throw SyntaxError();

    bottomRight = parseCoordinate(ss);
}

void Instruction::parseOperator(std::istream& ss)
{
    std::string token;
    ss >> token;
    if (token == "turn")
    {
        ss >> token;
        if (token == "on")
            op = TurnOn;
        else if (token == "off")
            op = TurnOff;
        else throw SyntaxError();
    }
    else if (token == "toggle")
        op = Toggle;
    else throw SyntaxError();
}

std::vector<size_t> Instruction::splitInts(const std::string& str)
{
    std::vector<size_t> ret;
    std::string token;
    std::istringstream ss(str);

    while (getline(ss, token, ','))
        ret.push_back(std::stoi(token));

    return ret;
}

Instruction::Coordinate Instruction::parseCoordinate(std::istream& ss)
{
    std::string token;
    ss >> token;

    auto numbers = splitInts(token);
    if (numbers.size() != 2)
        throw SyntaxError();

    return Coordinate{ numbers[0], numbers[1] };
}
