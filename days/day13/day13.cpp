#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <numeric>

class SeatingSolver
{
    std::vector<std::vector<int>> m_happinessMatrix;
    std::map<std::string, size_t> m_nameToIdx;

public:
    void addPair(const std::string &person, const std::string &neighbour, int happiness)
    {
        size_t idx1 = idxForName(person), idx2 = idxForName(neighbour);

        m_happinessMatrix[idx1][idx2] = happiness;
    }

    int findOptimalHappiness()
    {
        size_t numPeople = m_nameToIdx.size();
        std::vector<size_t> arrangement(numPeople);
        iota(arrangement.begin(), arrangement.end(), 0);

        int optimal = std::numeric_limits<int>::min();
        do
        {
            int happiness = 0;
            for (size_t i = 0; i != numPeople; ++i)
            {
                size_t person = arrangement[i];
                size_t leftNeighbour = arrangement[i == 0 ? numPeople - 1 : i - 1];
                size_t rightNeighbour = arrangement[i == numPeople - 1 ? 0 : i + 1];

                happiness += m_happinessMatrix[person][leftNeighbour];
                happiness += m_happinessMatrix[person][rightNeighbour];
            }
            
            optimal = std::max(happiness, optimal);
        }
        while (next_permutation(arrangement.begin(), arrangement.end()));

        return optimal;
    }

    std::vector<std::string> getNames() const
    {
        std::vector<std::string> ret;

        for (const auto &entry : m_nameToIdx)
            ret.push_back(entry.first);
        
        return ret;
    }

private:
    size_t idxForName(const std::string &name)
    {
        auto it = m_nameToIdx.find(name);
        if (it != m_nameToIdx.end())
            return it->second;

        size_t newIdx = m_nameToIdx.size();
        resizeMatrix(newIdx + 1);

        return m_nameToIdx[name] = newIdx;
    }

    void resizeMatrix(size_t size)
    {
        m_happinessMatrix.resize(size);
        for (auto & row : m_happinessMatrix)
            row.resize(size);
    }
};

int main(int, char **)
{
    static const std::regex pattern("(\\w+) would (gain|lose) (\\d+) happiness units by sitting next to (\\w+).");
    std::map<std::string, std::map<std::string, size_t>> distances;
    SeatingSolver solver;

    std::string line;
    while (getline(std::cin, line))
    {
        std::smatch match;
        if (regex_match(line, match, pattern))
            solver.addPair(match[1].str(), match[4].str(), (match[2].str() == "lose" ? -1 : 1) * stoi(match[3].str()));
        else
            std::cout << "Could not parse line '" << line << '\'' << std::endl;
    }

    std::cout << "The total change in happiness for the optimal seating arrangement is: " << solver.findOptimalHappiness() << std::endl;

    for (const auto &name : solver.getNames())
    {
        solver.addPair("Myself", name, 0);
        solver.addPair(name, "Myself", 0);
    }

    std::cout << "When including yourself, the total change in happiness for the optimal seating arrangement is: " << solver.findOptimalHappiness() << std::endl;
}
