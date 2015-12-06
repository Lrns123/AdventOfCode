#include <iostream>
#include <string>
#include "instruction.hpp"

int main(int, char **)
{
    static bool lightGrid[1000][1000] = { false };
    static size_t lightIntensity[1000][1000] = { 0 };

    std::string line;
    try
    {
        while (getline(std::cin, line))
            Instruction(line).apply(lightGrid).apply(lightIntensity);

        size_t lightsOn = 0;
        size_t brightness = 0;
        for (size_t x = 0; x != 1000; ++x)
            for (size_t y = 0; y != 1000; ++y)
            {
                if (lightGrid[x][y])
                    ++lightsOn;

                brightness += lightIntensity[x][y];
            }

        std::cout << "Lights on: " << lightsOn << std::endl;
        std::cout << "Brightness: " << brightness << std::endl;
    }
    catch (const SyntaxError &)
    {
        std::cout << "Syntax error occured while parsing '" << line << '\'' << std::endl;
    }    
}