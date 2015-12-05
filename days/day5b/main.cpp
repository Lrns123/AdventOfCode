#include <iostream>
#include <string>


bool isNice(const std::string &str)
{
    bool hasRepeat = false;

    // Search repeats with a single character inbetween
    for (int i = 0, n = str.size() - 2; i != n; ++i)
    {
        if (str[i] == str[i + 2])
        {
            hasRepeat = true;
            break;
        }
    }

    if (!hasRepeat)
        return false;

    // Search non-overlapping pairs
    for (int i = 0, n = str.size() - 1; i != n; ++i)
    {
        char pattern[2] = { str[i], str[i + 1] };

        for (int j = 0, m = str.size() - 1; j != m; ++j)
        {
            // Skip area around search pattern (would be an overlapped match)
            if (j > i - 2 && j < i + 2)
                continue;

            if (str[j] == pattern[0] && str[j + 1] == pattern[1])
            {
                return true;
            }
        }
    }

    return false;
}

int main(int, char **)
{
    size_t niceStrings = 0;
    std::string line;
    while (getline(std::cin, line))
    {
        if (isNice(line))
            ++niceStrings;
    }

    std::cout << "Nice strings: " << niceStrings << std::endl;
}