#include <iostream>
#include <string>


bool isNice(const std::string &str)
{
    char prev = 0;
    size_t vowels = 0;
    bool hasDouble = false;

    for (char ch : str)
    {
        switch (ch)
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            ++vowels;
            break;
        case 'b':
            if (prev == 'a')
                return false;
            break;
        case 'd':
            if (prev == 'c')
                return false;
            break;
        case 'q':
            if (prev == 'p')
                return false;
            break;
        case 'y':
            if (prev == 'x')
                return false;
            break;
        default:
            break;
        }
        
        if (!hasDouble && ch == prev)
            hasDouble = true;

        prev = ch;
    }

    return vowels > 2 && hasDouble;
}

bool isReallyNice(const std::string &str)
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
    size_t reallyNiceStrings = 0;

    std::string line;
    while (getline(std::cin, line))
    {
        if (isNice(line))
            ++niceStrings;

        if (isReallyNice(line))
            ++reallyNiceStrings;
    }

    std::cout << "Nice strings: " << niceStrings << std::endl;
    std::cout << "Really nice strings: " << reallyNiceStrings << std::endl;
}