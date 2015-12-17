#include <iostream>
#include <string>
#include "logicnetwork.hpp"

int main(int, char **)
{
    std::string line;
    try
    {
        LogicNetwork network;
        while (getline(std::cin, line))
            network.addGate(line);

        std::cout << "The value of a is: " << network.evaluate("a") << std::endl;

        std::cout << "Overriding b with the value of a." << std::endl;
        network.addGate(std::to_string(network.evaluate("a")) + " -> b");
        network.reset();
        
        std::cout << "The value of a is now: " << network.evaluate("a") << std::endl;
    }
    catch (const SyntaxError &)
    {
        std::cout << "Syntax error occured while parsing '" << line << '\'' << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception occured: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown error occured while parsing '" << line << '\'' << std::endl;
    }
}
