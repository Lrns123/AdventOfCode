#include <iostream>
#include <string>
#include "logicgates.hpp"
#include "logicnetwork.hpp"

int main(int, char **)
{
    std::string line;
    try
    {
        LogicNetwork network;

        while (getline(std::cin, line))
            network.parseLine(line);

        network.resolve();
        
        std::cout << "The value of a is: " << network.evaluate("a") << std::endl;
        std::cout << "Overriding b to the value of a." << std::endl;

        network.parseLine(std::to_string(network.evaluate("a")) + " -> b");
        network.resolve();
        network.reset();

        std::cout << "The value of a is now: " << network.evaluate("a") << std::endl;
    }
    catch (const SyntaxError &)
    {
        std::cout << "Syntax error occured while parsing '" << line << '\'' << std::endl;
    }
    catch (const InvalidGateException &e)
    {
        std::cout << "Invalid gate setup: '" << e.what() << std::endl;
    }    
    catch (const std::exception &e)
    {
        std::cout << "Error occured while parsing '" << line << "\': " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown error occured while parsing '" << line << '\'' << std::endl;
    }
}
