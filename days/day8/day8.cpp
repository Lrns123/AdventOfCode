#include <iostream>
#include <string>

size_t getEscapedLength(const std::string &string)
{
    size_t length = 0;

    for (auto it = string.begin(), eit = string.end(); it != eit; ++it)
    {
        if (*it == '\"')
            ++length;

        if (*it == '\\')
            ++length;

        ++length;
    }

    return length + 2; // Add 2 to account for the new surrounding double-quotes
}

size_t getMemoryLength(const std::string &string)
{
    size_t length = 0;

    for (auto it = string.begin(), eit = string.end(); it != eit; ++it)
    {
        if (*it == '\"')
            continue;

        if (*it == '\\')
        {
            ++length;
            ++it;
            if (*it == 'x')
                it += 2;
            
            
            continue;
        }

        ++length;
    }

    return length;
}

int main(int, char **)
{
    size_t rawLength = 0;
    size_t memoryLength = 0;
    size_t escapedLength = 0;

    std::string line;
    while (getline(std::cin, line))
    {
        rawLength += line.size();
        memoryLength += getMemoryLength(line);
        escapedLength += getEscapedLength(line);
    }

    std::cout << "Raw length: " << rawLength << std::endl;
    std::cout << "In-memory length: " << memoryLength << std::endl;
    std::cout << "Escaped length: " << escapedLength << std::endl;
    std::cout << "(Raw - in-memory): " << (rawLength - memoryLength) << std::endl;
    std::cout << "(Escaped - raw): " << (escapedLength - rawLength) << std::endl;
}
