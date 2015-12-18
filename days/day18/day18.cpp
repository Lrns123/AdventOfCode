#include <iostream>

unsigned neighbours(bool (&grid)[100][100], unsigned x, unsigned y)
{
    unsigned count = 0;
    for (unsigned i = x == 0 ? 0 : x - 1 , mi = x == 99 ? 99 : x + 1; i <= mi; ++i)
        for (unsigned j = y == 0 ? 0 : y - 1, mj = y == 99 ? 99 : y + 1; j <= mj; ++j)
            if (grid[i][j])
                ++count;

    return grid[x][y] ? count - 1 : count;
}

void update(bool (&currentGrid)[100][100], bool (&newGrid)[100][100], bool cornersFixed = false)
{
    for (unsigned i = 0; i != 100; ++i)
        for (unsigned j = 0; j != 100; ++j)
        {
            unsigned n = neighbours(currentGrid, i, j);
            newGrid[i][j] = currentGrid[i][j] ? n == 2 || n == 3 : n == 3;
        }

    if (cornersFixed)
        newGrid[0][0] = newGrid[0][99] = newGrid[99][0] = newGrid[99][99] = true;
}

unsigned countLights(bool (&grid)[100][100])
{
    unsigned count = 0;
    for (unsigned i = 0; i != 100; ++i)
        for (unsigned j = 0; j != 100; ++j)
            if (grid[i][j])
                ++count;

    return count;
}

int main(int, char**)
{
    // Grid (index [2] holds the input grid, index [0] and [1] alternatingly contain the current and previous state)
    static bool grid[3][100][100] = { 0 };

    // Read grid
    char c;
    for (unsigned i = 0; i != 100; ++i)
        for (unsigned j = 0; j != 100; ++j)
            std::cin >> c, grid[0][i][j] = grid[2][i][j] = c == '#';

    // Update grid
    for (unsigned i = 0; i != 100; ++i)
        update(grid[i & 1], grid[(i & 1) ^ 1]);   
    
    std::cout << "Lights on after 100 updates: " << countLights(grid[100 & 1]) << std::endl;

    // Restore initial grid
    memcpy(grid[0], grid[2], sizeof grid[0]);

    // Update grid
    for (unsigned i = 0; i != 100; ++i)
        update(grid[i & 1], grid[(i & 1) ^ 1], true);

    std::cout << "Lights on after 100 updates (corners forced on): " << countLights(grid[100 & 1]) << std::endl;
}