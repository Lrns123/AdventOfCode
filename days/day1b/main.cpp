#include <iostream>

// Advent of code - Day 1b
int main(int, char **)
{
    int floor = 0;
    int position = 0;
    char c;
    
    while (std::cin >> c)
    {
        ++position;

        if (c == ')')
            --floor;
        else if (c == '(')
            ++floor;

        if (floor < 0)
        {
            std::cout << "Santa entered the basement on position " << position << std::endl;
            break;
        }
    }
}