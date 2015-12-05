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