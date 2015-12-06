#pragma once
#include <string>
#include <vector>

class SyntaxError
{};


class Instruction
{
    enum Operator
    {
        TurnOn,
        TurnOff,
        Toggle
    };

    struct Coordinate
    {
        size_t x, y;
    };

    Operator op;
    Coordinate topLeft;
    Coordinate bottomRight;

public:
    explicit Instruction(const std::string& instruction);

    // Part one
    const Instruction& apply(bool (&grid)[1000][1000]) const;

    // Part two
    const Instruction& apply(size_t (&grid)[1000][1000]) const;

private:
    void parse(const std::string& instruction);
    void parseOperator(std::istream& ss);
    static std::vector<size_t> splitInts(const std::string& str);
    static Coordinate parseCoordinate(std::istream& ss);
};