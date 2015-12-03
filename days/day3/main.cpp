#include <iostream>
#include <set>

struct Coordinate
{
    int x;
    int y;

    Coordinate(int x, int y)
        : x(x), y(y)
    {}

    bool operator<(const Coordinate &rhs) const
    {
        if (x < rhs.x)
            return true;

        if (x == rhs.x && y < rhs.y)
            return true; 

        return false;
    }
};

int main(int, char **)
{
    Coordinate pos = { 0, 0 };
    char c;

    std::set<Coordinate> houses { pos };

    while (std::cin >> c)
    {
        if (c == '^') ++pos.y;
        if (c == 'v') --pos.y;
        if (c == '>') ++pos.x;
        if (c == '<') --pos.x;

        houses.insert(pos);
    }

    std::cout << "Houses visited: " << houses.size() << std::endl;
}