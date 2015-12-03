#include <iostream>

// Advent of code - Day 1
int main(int, char **)
{
    int floor = 0;
    char c;

    while (std::cin >> c)
    {
        if (c == ')')
            --floor;
        else if (c == '(')
            ++floor;
    }

    std::cout << "Santa is on floor " << floor << std::endl;
}