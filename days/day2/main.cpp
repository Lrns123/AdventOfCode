#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> tokenize(string input, char separator)
{
    vector<int> result;
    istringstream stream(input);

    std::string token;
    while (getline(stream, token, separator))
        result.emplace_back(stoi(token));

    return move(result);
}

class Package
{
    size_t length;
    size_t width;
    size_t height;

public:
    explicit Package(string dimensions)
    {
        auto tokens = tokenize(dimensions, 'x');
        length = tokens[0];
        width = tokens[1];
        height = tokens[2];
    }

    size_t surfaceArea() const
    {
        return 2 * length * width + 2 * width * height + 2 * height * length;
    }

    size_t slack() const
    {
        const int side1 = length * width;
        const int side2 = width * height;
        const int side3 = height * length;

        return min(min(side1, side2), side3);
    }

    size_t paperRequired() const
    {
        return surfaceArea() + slack();
    }

};

// Advent of code - Day 2
int main(int, char **)
{
    size_t paperRequried = 0;
    
    string line;
    while (getline(cin, line))
        paperRequried += Package(line).paperRequired();
    
    cout << "The paper required is: " << paperRequried << " square feet." << endl;
}