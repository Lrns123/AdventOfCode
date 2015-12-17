#pragma once
#include <map>

class SyntaxError
{};

class LogicNetwork
{
    struct LogicGate
    {
        std::string operands[2];
        unsigned short(*op)(unsigned short, unsigned short);
        unsigned int memoized;
    };

    std::map<std::string, LogicGate> m_gates;

public:
    LogicNetwork();

    void addGate(const std::string &definition);
    void reset();

    unsigned short evaluate(const std::string &wire);
};
