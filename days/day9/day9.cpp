#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>

class CityVisitor
{
    std::vector<std::vector<size_t>> m_distanceMatrix;
    std::map<std::string, size_t> m_nameToIdx;

public:
    void addDistance(const std::string &city1, const std::string &city2, size_t distance)
    {
        size_t idx1 = idxForName(city1);
        size_t idx2 = idxForName(city2);

        m_distanceMatrix[idx1][idx2] = distance;
        m_distanceMatrix[idx2][idx1] = distance;
    }

    void findPath(size_t &shortest, size_t &longest)
    {
        size_t numCities = m_nameToIdx.size();
        std::vector<size_t> path;

        for (size_t i = 0; i != numCities; ++i)
            path.push_back(i);

        shortest = std::numeric_limits<size_t>::max();
        longest = std::numeric_limits<size_t>::min();

        do
        {
            size_t pathLength = 0;
            for (size_t i = 1; i != numCities; ++i)
            {
                size_t src = path[i - 1];
                size_t dst = path[i];
                pathLength += m_distanceMatrix[src][dst];
            }

            if (pathLength < shortest)
                shortest = pathLength;

            if (pathLength > longest)
                longest = pathLength;

        } while (next_permutation(path.begin(), path.end()));
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
        m_distanceMatrix.resize(size);
        for (auto & row : m_distanceMatrix)
            row.resize(size);
    }
};

static const std::regex pattern("(\\w+) to (\\w+) = (\\d+)");
int main(int, char **)
{
    using distanceMap = std::map<std::string, std::map<std::string, size_t>>;
    distanceMap distances;

    std::string line;
    std::smatch match;
    CityVisitor visitor;

    while (getline(std::cin, line))
    {
        if (regex_match(line, match, pattern))
            visitor.addDistance(match[1].str(), match[2].str(), stoul(match[3].str()));
        else
            std::cout << "Could not parse line '" << line << '\'' << std::endl;
    }

    size_t shortest, longest;
    visitor.findPath(shortest, longest);

    std::cout << "The shortest path is " << shortest << std::endl;
    std::cout << "The longest path is " << longest << std::endl;
}
