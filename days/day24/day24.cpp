#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

// Helper class to enumerate combinations
class Combinations
{
    std::vector<bool> m_mask;
    std::vector<size_t> m_indices;

public:
    using iterator = std::vector<size_t>::iterator;
    using const_iterator = std::vector<size_t>::const_iterator;

    Combinations(unsigned n, unsigned k)
        : m_mask(k, true), m_indices(k)
    {
        m_mask.resize(n, false);
        for (size_t i = 0, j = 0, n = m_mask.size(); i != n; ++i)
            if (m_mask[i]) m_indices[j++] = i;
    }

    bool next()
    {
        if (!prev_permutation(m_mask.begin(), m_mask.end()))
            return false;
        for (size_t i = 0, j = 0, n = m_mask.size(); i != n; ++i)
            if (m_mask[i]) m_indices[j++] = i;
        return true;
    }

    // Returns the input array with the current combination filtered out.
    template <typename T>
    std::vector<T> filtered(const std::vector<T> &input)
    {
        std::vector<T> ret;
        ret.reserve(input.size());

        for (size_t i = 0, n = input.size(); i != n; ++i)
            if (!m_mask[i]) ret.push_back(input[i]);

        return ret;
    }
    
    iterator begin() { return m_indices.begin(); }
    const_iterator begin() const { return m_indices.begin(); }
    iterator end() { return m_indices.end(); }
    const_iterator end() const { return m_indices.end(); }
};

// Guess initial value for k. Assumes the vector is sorted in descending order.
unsigned guessInitialK(const std::vector<unsigned> &presents, unsigned targetSum)
{
    unsigned sum = 0;
    for (auto it = presents.begin(), eit = presents.end(); it != eit; ++it)
        if ((sum += *it) >= targetSum)
            return distance(presents.begin(), it) + 1;

    return 1;
}

bool checkCompartments(const std::vector<unsigned> &presents, unsigned targetSum)
{
    unsigned totalSum = accumulate(presents.begin(), presents.end(), 0);
    
    if (totalSum == targetSum)
        return true;

    if (totalSum < targetSum)
        return false;

    for (unsigned k = guessInitialK(presents, targetSum), n = presents.size(); k != n; ++k)
    {
        Combinations c(n, k);
        do
        {
            unsigned sum = 0;
            unsigned long long QE = 1;
            for (auto idx : c)
                sum += presents[idx], QE *= presents[idx];

            if (sum == targetSum && checkCompartments(c.filtered(presents), targetSum))
                return true;

        }
        while (c.next());
    }
    return false;
}

unsigned long long findMinimalEntanglement(const std::vector<unsigned> &presents, unsigned targetSum)
{    
    unsigned long long minQE = std::numeric_limits<unsigned long long>::max();

    for (unsigned k = guessInitialK(presents, targetSum), n = presents.size(); k != n; ++k)
    {
        Combinations c(n, k);
        do
        {
            unsigned sum = 0;
            unsigned long long QE = 1;
            for (auto idx : c)
                sum += presents[idx], QE *= presents[idx];

            if (sum == targetSum && QE < minQE && checkCompartments(c.filtered(presents), targetSum))
                minQE = QE;
        }
        while (c.next());
        
        if (minQE < std::numeric_limits<unsigned long long>::max())
            break;
    }
    
    return minQE;
}

int main(int, char **)
{
    std::vector<unsigned> presents(std::istream_iterator<unsigned>{std::cin}, {});
    unsigned sum = accumulate(presents.begin(), presents.end(), 0);

    // Sort in descending order for optimal performance.
    sort(presents.begin(), presents.end(), [](auto lhs, auto rhs) { return lhs > rhs; });

    std::cout << "Minimal quantum entanglement (3 groups): " << findMinimalEntanglement(presents, sum / 3) << std::endl;
    std::cout << "Minimal quantum entanglement (4 groups): " << findMinimalEntanglement(presents, sum / 4) << std::endl;
}
