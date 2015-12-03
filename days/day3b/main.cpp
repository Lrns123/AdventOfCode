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
    Coordinate santaPos = { 0, 0 };
    Coordinate roboSantaPos = { 0, 0 };
    size_t step = 0;
    char c;

    std::set<Coordinate> houses { {0, 0} };

    while (std::cin >> c)
    {
        auto &pos = (++step & 1) ? santaPos : roboSantaPos;

        if (c == '^') ++pos.y;
        if (c == 'v') --pos.y;
        if (c == '>') ++pos.x;
        if (c == '<') --pos.x;

        houses.insert(pos);
    }

    std::cout << "Houses visited: " << houses.size() << std::endl;
}