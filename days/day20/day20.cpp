#include <iostream>
#include <vector>
#include <algorithm>

unsigned findHouse(unsigned target, unsigned numHouses, unsigned presentsPerElf, unsigned maxVisits)
{
    unsigned houseNumber = numHouses;
    std::vector<unsigned> presents(numHouses);

    for (unsigned elf = 1, elfPresents = presentsPerElf; elf != numHouses; ++elf, elfPresents += presentsPerElf)
        for (unsigned house = elf, visitsRemaining = maxVisits; house < numHouses && visitsRemaining; house += elf, --visitsRemaining)
            if ((presents[house] += elfPresents) >= target)
                houseNumber = std::min(houseNumber, house);

    return houseNumber;
}

int main(int argc, char **argv)
{
    unsigned presentTarget;
    unsigned numHouses = (argc < 2) ? 1000000 : atoi(argv[1]);

    std::cin >> presentTarget;
    std::cout << "Searching up to " << numHouses << " houses." << std::endl << std::endl;
    
    std::cout << "Presents per elf: 10. Max visits: unlimited." << std::endl;
    std::cout << "First house with more than " << presentTarget << " presents: " << findHouse(presentTarget, numHouses, 10, std::numeric_limits<unsigned>::max()) << std::endl;

    std::cout << std::endl << "Presents per elf: 11. Max visits: 50." << std::endl;
    std::cout << "First house with more than " << presentTarget << " presents: " << findHouse(presentTarget, numHouses, 11, 50) << std::endl;
}
