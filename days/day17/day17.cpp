#include <vector>
#include <iostream>
#include <iterator>
#include <map>

bool isValid(const std::vector<unsigned> &sizes, unsigned combination, unsigned &numContainers)
{
    unsigned sum = 0;
    numContainers = 0;
    for (auto size : sizes)
    {
        if (combination & 1 && (++numContainers, sum += size) > 150)
            return false;

        combination >>= 1;
    }

    return sum == 150;
}

int main(int, char**)
{
    std::vector<unsigned> containerSizes{std::istream_iterator<unsigned>(std::cin), {}};
    std::map<unsigned, unsigned> configurations;

    if (containerSizes.size() > sizeof(unsigned) * 8 - 1)
        return 1;

    unsigned combinations = 0;
    for (unsigned i = 0, n = 1 << containerSizes.size(), numContainers; i != n; ++i)
        if (isValid(containerSizes, i, numContainers))
            ++combinations, ++configurations[numContainers];
        
    std::cout << "Number of container combinations: " << combinations << std::endl;
    std::cout << "Configurations with fewest number of containers: " << configurations.begin()->second << std::endl;
}