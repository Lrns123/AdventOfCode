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
    Coordinate soloPos = { 0, 0 };

    Coordinate santaPos = { 0, 0 };
    Coordinate roboPos = { 0, 0 };
    char c;

    bool roboSantaTurn = false;

    std::set<Coordinate> housesVisitedSolo{ {0, 0} };
    std::set<Coordinate> housesVisitedCoop{ {0, 0} };

    while (std::cin >> c)
    {
        auto &coopPos = roboSantaTurn ? roboPos : santaPos;

        roboSantaTurn = !roboSantaTurn;

        if (c == '^')
        {
            ++soloPos.y;
            ++coopPos.y;
        }
        if (c == 'v')
        {
            --soloPos.y;
            --coopPos.y;
        }
        if (c == '>')
        {
            ++soloPos.x;
            ++coopPos.x;
        }
        if (c == '<')
        {
            --soloPos.x;
            --coopPos.x;
        }

        housesVisitedSolo.insert(soloPos);
        housesVisitedCoop.insert(coopPos);
    }

    std::cout << "Houses visited alone: " << housesVisitedSolo.size() << std::endl;
    std::cout << "Houses visited with robo-santa: " << housesVisitedCoop.size() << std::endl;
}