#include "logicnetwork.hpp"
#include <vector>
#include <sstream>
#include <iterator>

namespace
{
    std::vector<std::string> splitTokens(const std::string &line)
    {
        std::vector<std::string> ret;
        ret.reserve(5);
        
        std::istringstream ss(line);
        copy(std::istream_iterator<std::string>(ss), {}, back_inserter(ret));
        return ret;
    }

    // Operators
    using ushort = unsigned short;
    auto opIdent = [](ushort a, ushort) -> ushort { return a; };
    auto opNot = [](ushort a, ushort) -> ushort { return ~a & 0xFFFF; };
    auto opAnd = [](ushort a, ushort b) -> ushort { return a & b; };
    auto opOr = [](ushort a, ushort b) -> ushort { return a | b; };
    auto opLShift = [](ushort a, ushort b) -> ushort { return a << b; };
    auto opRShift = [](ushort a, ushort b) -> ushort { return a >> b; };

    // Default value for LogicGate::memoized.
    enum : unsigned int { NotMemoized = 0xFFFFFFFF };
}

LogicNetwork::LogicNetwork()
{
}

void LogicNetwork::addGate(const std::string& definition)
{
    std::vector<std::string> tokens(splitTokens(definition));

    if (tokens.size() < 3 || tokens[tokens.size() - 2] != "->")
        throw SyntaxError();

    const auto &wireName = tokens.back();

    if (tokens.size() == 3)
        // <a> -> <w>
        m_gates[wireName] = { tokens[0], {}, opIdent, NotMemoized };
    else if (tokens.size() == 4 && tokens[0] == "NOT")
        // NOT <a> -> <w>
        m_gates[wireName] = { tokens[1], {}, opNot, NotMemoized };
    else if (tokens.size() == 5)
    {
        // <a> <op> <b> -> <w>
        const auto &op = tokens[1];

        if (op == "AND")
            m_gates[wireName] = { tokens[0], tokens[2], opAnd, NotMemoized };
        else if (op == "OR")
            m_gates[wireName] = { tokens[0], tokens[2], opOr, NotMemoized };
        else if (op == "LSHIFT")
            m_gates[wireName] = { tokens[0], tokens[2], opLShift, NotMemoized };
        else if (op == "RSHIFT")
            m_gates[wireName] = { tokens[0], tokens[2], opRShift, NotMemoized };
        else
            throw SyntaxError();
    }
    else
        throw SyntaxError();

}

void LogicNetwork::reset()
{
    for (auto &gate : m_gates)
        gate.second.memoized = NotMemoized;
}

unsigned short LogicNetwork::evaluate(const std::string& wire)
{
    if (wire.empty())
        return 0;

    if (isdigit(wire.front()))
        return stoul(wire) & 0xFFFF;

    auto it = m_gates.find(wire);
    if (it == m_gates.end())
        throw std::runtime_error("Cannot find gate " + wire);
    
    auto &gate = it->second;
    if (gate.memoized != NotMemoized)
        return gate.memoized;

    return gate.memoized = gate.op(evaluate(gate.operands[0]), evaluate(gate.operands[1]));
}

