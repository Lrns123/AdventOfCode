#pragma once
#include <map>
#include <memory>
#include "logicgates.hpp"

class SyntaxError
{};

class LogicNetwork
{
    std::map<std::string, std::unique_ptr<LogicGate>> gates;
    std::map<std::string, std::pair<std::string, std::string>> dependencyTable;

public:
    LogicNetwork();

    void parseLine(const std::string &line);
    void resolve();
    void reset();

    unsigned short evaluate(const std::string &wire) const;

private:
    void setDependencies(const std::string &gate, const std::string &input);
    void setDependencies(const std::string &gate, const std::string &input1, const std::string &input2);
    LogicGate *getGate(const std::string& name);
};
