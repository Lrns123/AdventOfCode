#include "logicnetwork.hpp"
#include <vector>
#include <sstream>

namespace
{
    std::vector<std::string> splitTokens(const std::string &line, int reserve = 0)
    {
        std::vector<std::string> tokens;
        if (reserve)
            tokens.reserve(reserve);

        using Iter = std::istream_iterator<std::string>;
        std::istringstream ss(line);
        copy(Iter(ss), Iter(), back_inserter(tokens));

        return tokens;
    }
}

LogicNetwork::LogicNetwork()
{
}

void LogicNetwork::parseLine(const std::string& line)
{
    std::vector<std::string> tokens = splitTokens(line, 5);

    if (tokens.size() < 3 || tokens[tokens.size() - 2] != "->")
        throw SyntaxError();

    const auto &wireName = tokens.back();

    if (tokens.size() == 3)
    {
        // <a> -> <w>
        gates[wireName] = std::make_unique<IdentityGate>();
        setDependencies(wireName, tokens[0]);
    }
    else if (tokens.size() == 4 && tokens[0] == "NOT")
    {
        // NOT <a> -> <w>
        gates[wireName] = std::make_unique<NotGate>();
        setDependencies(wireName, tokens[1]);
    }
    else if (tokens.size() == 5)
    {
        // <a> <op> <b> -> <w>
        const auto &op = tokens[1];

        if (op == "AND")
        {
            gates[wireName] = std::make_unique<AndGate>();
            setDependencies(wireName, tokens[0], tokens[2]);
        }
        else if (op == "OR")
        {
            gates[wireName] = std::make_unique<OrGate>();
            setDependencies(wireName, tokens[0], tokens[2]);
        }
        else if (op == "LSHIFT")
        {
            gates[wireName] = std::make_unique<LShiftGate>(stoi(tokens[2]));
            setDependencies(wireName, tokens[0]);
        }
        else if (op == "RSHIFT")
        {
            gates[wireName] = std::make_unique<RShiftGate>(stoi(tokens[2]));
            setDependencies(wireName, tokens[0]);
        }
        else
            throw SyntaxError();
    }
    else
        throw SyntaxError();

}

void LogicNetwork::resolve()
{
    for (auto &entry : dependencyTable)
    {
        auto &gate = gates.at(entry.first);
        auto &dependencies = entry.second;

        if (!dependencies.first.empty())
            gate->setInput(0, getGate(dependencies.first));

        if (!dependencies.second.empty())
            gate->setInput(1, getGate(dependencies.second));
    }
}

void LogicNetwork::reset()
{
    for (auto &gate : gates)
        gate.second->resetCache();
}

unsigned short LogicNetwork::evaluate(const std::string& wire) const
{
    return gates.at(wire)->evaluate();
}

void LogicNetwork::setDependencies(const std::string& gate, const std::string& input)
{
    dependencyTable[gate] = std::make_pair(input, std::string());
}

void LogicNetwork::setDependencies(const std::string& gate, const std::string& input1, const std::string &input2)
{
    dependencyTable[gate] = std::make_pair(input1, input2);
}

LogicGate* LogicNetwork::getGate(const std::string& name)
{
    auto it = gates.find(name);
    if (it != gates.end())
        return it->second.get();

    if (isdigit(name.front()))
        return (gates[name] = std::make_unique<ConstantGate>(stoi(name))).get();
    
    throw InvalidGateException("Cannot find gate");
}
