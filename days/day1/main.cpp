#include <iostream>

// Advent of code - Day 1
int main(int, char **)
{
    int floor = 0, position = 0;
    bool basementEntered = false;
    char c;

    while (std::cin >> c)
    {
        ++position;

        if (c == ')')
            --floor;
        else if (c == '(')
            ++floor;

        if (floor < 0 && !basementEntered)
        {
            basementEntered = true;
            std::cout << "Santa entered the basement on position " << position << std::endl;
        }
    }

    std::cout << "Santa is on floor " << floor << std::endl;
}