#include <iostream>
#include <vector>
#include <algorithm>

namespace
{
    void findMinimalEntanglement(const std::vector<unsigned> &presents, unsigned i, unsigned subSum, unsigned length, unsigned long long QE, unsigned targetSum, unsigned &minLength, unsigned long long &minQE)
    {
        if (subSum > targetSum || length > minLength || QE > minQE)
            return;

        if (subSum == targetSum)
        {
            minLength = length;
            minQE = QE;
            return;
        }

        for (unsigned n = presents.size(); i != n; ++i)
            findMinimalEntanglement(presents, i + 1, subSum + presents[i], length + 1, QE * presents[i], targetSum, minLength, minQE);
    }
}

unsigned long long findMinimalEntanglement(const std::vector<unsigned> &presents, unsigned targetSum)
{
    unsigned minSize = presents.size();
    unsigned long long minQE = std::numeric_limits<unsigned long long>::max();
    
    findMinimalEntanglement(presents, 0, 0, 0, 1, targetSum, minSize, minQE);

    return minQE;
}

int main(int, char **)
{
    std::vector<unsigned> presents;
    
    unsigned size, sum = 0;
    while (std::cin >> size)
        presents.push_back(size), sum += size;

    // Sort in descending order
    std::sort(presents.begin(), presents.end(), [](const auto &lhs, const auto &rhs) { return lhs > rhs; });
   
    std::cout << "Minimal quantum entanglement (3 groups): " << findMinimalEntanglement(presents, sum / 3) << std::endl;
    std::cout << "Minimal quantum entanglement (4 groups): " << findMinimalEntanglement(presents, sum / 4) << std::endl;   
}
