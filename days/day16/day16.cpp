#include <map>
#include <regex>
#include <iostream>
#include <functional>

namespace
{
    const struct
    {
        std::string prop;
        int val;
        std::function<bool(int, int)> op;
    }
    targetProperties[]
    {
        { "children",    3, std::equal_to<int>() },
        { "cats",        7, std::greater<int>() },
        { "samoyeds",    2, std::equal_to<int>() },
        { "pomeranians", 3, std::less<int>() },
        { "akitas",      0, std::equal_to<int>() },
        { "vizslas",     0, std::equal_to<int>() },
        { "goldfish",    5, std::less<int>() },
        { "trees",       3, std::greater<int>() },
        { "cars",        2, std::equal_to<int>() },
        { "perfumes",    1, std::equal_to<int>() }
    };
}

bool matchProperties(const std::map<std::string, int> &properties, bool ignoreOp)
{
    for (const auto &targetProp : targetProperties)
    {
        auto it = properties.find(targetProp.prop);
        if (it == properties.end())
            continue;

        if (ignoreOp)
        {
            if (it->second != targetProp.val)
                return false;
        }
        else if (!targetProp.op(it->second, targetProp.val))
            return false;
    }
    return true;
}

int main(int, char**)
{
    static std::regex inputRegex("Sue \\d+: (\\w+): (-?\\d+), (\\w+): (-?\\d+), (\\w+): (-?\\d+)");
    std::vector<std::map<std::string, int>> sues;
    
    std::string input;
    while (getline(std::cin, input))
    {
        std::smatch match;
        if (regex_match(input, match, inputRegex))
            sues.emplace_back(std::map<std::string, int>{
                { match[1].str(), stoi(match[2].str()) },
                { match[3].str(), stoi(match[4].str()) },
                { match[5].str(), stoi(match[6].str()) }
            });
        else
            std::cout << "Cannot parse line '" << input << '\'' << std::endl;
    }

    size_t sueNum = 1;
    for (const auto &sue : sues)
    {
        if (matchProperties(sue, true))
            std::cout << "Match found for Sue " << sueNum << std::endl;
        
        if (matchProperties(sue, false))
            std::cout << "Match found for real Sue " << sueNum << std::endl;

        ++sueNum;
    }
}