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
    std::set<Coordinate> visitedSolo{ { 0, 0 } }, visitedCoop{ { 0, 0 } };
    Coordinate soloPos{ 0, 0 }, santaPos{ 0,0 }, roboPos{ 0, 0 };
    
    bool roboSantaTurn = false;
    char c;

    while (std::cin >> c)
    {
        auto &coopPos = (roboSantaTurn ^= 1) ? roboPos : santaPos;

        if (c == '^')
            ++soloPos.y, ++coopPos.y;
        
        if (c == 'v')
            --soloPos.y, --coopPos.y;

        if (c == '>')
            ++soloPos.x, ++coopPos.x;
        
        if (c == '<')
            --soloPos.x, --coopPos.x;

        visitedSolo.insert(soloPos);
        visitedCoop.insert(coopPos);
    }

    std::cout << "Houses visited alone: " << visitedSolo.size() << std::endl;
    std::cout << "Houses visited with robo-santa: " << visitedCoop.size() << std::endl;
}