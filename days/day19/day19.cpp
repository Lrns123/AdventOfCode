#include <iostream>
#include <vector>
#include <regex>
#include <set>

using RuleSet = std::vector<std::pair<std::string, std::string>>;

unsigned distinctTransformations(const std::string &molecule, const RuleSet& rules)
{
    std::set<std::string> results;

    for (const auto &entry : rules)
        for (auto pos = molecule.find(entry.first, 0); pos != std::string::npos; pos = molecule.find(entry.first, pos + 1))
            results.emplace(move(std::string(molecule).replace(pos, entry.first.size(), entry.second)));

    return results.size();
}

unsigned constructionSteps(std::string molecule, const RuleSet & rules)
{  
    unsigned steps = 0;
    while (molecule != "e")
    {
        bool stuck = true;
        for (const auto &rule : rules)
        {
            size_t pos = molecule.find(rule.first);
            if (pos != molecule.npos)
            {
                stuck = false;
                ++steps;
                molecule.replace(pos, rule.first.size(), rule.second);
            }
        }
        
        if (stuck)
            return 0;
    }

    return steps;
}

int main(int, char**)
{
    static const std::regex inputRegex("(\\w+) => (\\w+)");
    RuleSet rules;
    std::string molecule;

    std::string line;
    while (getline(std::cin, line))
    {
        if (line.empty())
            break;
        
        std::smatch match;
        if (regex_match(line, match, inputRegex))
            rules.emplace_back(match[1], match[2]);
        else
            std::cout << "Could not parse line '" << line << '\'' << std::endl;
    }

    std::cin >> molecule;

    std::cout << "Distinct molecules: " << distinctTransformations(molecule, rules) << std::endl;
    
    // Swap rules
    for (auto &entry : rules)
        swap(entry.first, entry.second);

    std::cout << "Construction steps: " << constructionSteps(molecule, rules) << std::endl;
}
