#include "instruction.hpp"
#include <boost/tokenizer.hpp>

class InstructionTokenizer
{
    using tokenizer = boost::tokenizer<boost::char_separator<char>>;
    tokenizer tokens;
    tokenizer::const_iterator it;


public:
    InstructionTokenizer(const std::string &input)
        : tokens(input, boost::char_separator<char>(" ,")),
          it(tokens.begin())
    {}

    const std::string &next()
    {
        if (++it == tokens.end())
            throw SyntaxError();

        return *it;
    }

    const std::string &get() const
    {
        return *it;
    }
};

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
    InstructionTokenizer tokenizer(instruction);

    if (tokenizer.get() == "turn")
    {
        if (tokenizer.next() == "on")
            op = TurnOn;
        else if (tokenizer.get() == "off")
            op = TurnOff;
        else throw SyntaxError();
    }
    else if (tokenizer.get() == "toggle")
        op = Toggle;
    else throw SyntaxError();

    topLeft.x = stoi(tokenizer.next());
    topLeft.y = stoi(tokenizer.next());

    if (tokenizer.next() != "through")
        throw SyntaxError();

    bottomRight.x = stoi(tokenizer.next());
    bottomRight.y = stoi(tokenizer.next());
}