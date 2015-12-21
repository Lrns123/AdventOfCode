#include <iostream>
#include <algorithm>
#include <regex>

namespace
{
    struct Item
    {
        const char *name;
        unsigned cost;
        unsigned damage;
        unsigned armor;
    };

    const Item weapons[]
    {
        { "Dagger",     8,  4, 0 },
        { "Shortsword", 10, 5, 0 },
        { "Warhammer",  25, 6, 0 },
        { "Longsword",  40, 7, 0 },
        { "Greataxe",   74, 8, 0 },
    };

    const Item armors[]
    {
        { "None",       0,   0, 0 },
        { "Leather",    13,  0, 1 },
        { "Chainmail",  31,  0, 2 },
        { "Splintmail", 53,  0, 3 },
        { "Bandedmail", 75,  0, 4 },
        { "Platemail",  102, 0, 5 },
    };

    const Item rings[]
    {
        { "None",       0,   0, 0 },
        { "Damage +1",  25,  1, 0 },
        { "Damage +2",  50,  2, 0 },
        { "Damage +3",  100, 3, 0 },
        { "Defence +1", 20,  0, 1 },
        { "Defence +2", 40,  0, 2 },
        { "Defence +3", 80,  0, 3 },
    };

    struct Stats
    {
        unsigned hitPoints;
        unsigned damage;
        unsigned armor;
    };

    bool simulateFight(Stats player, Stats boss)
    {
        unsigned netPlayerDmg = player.damage <= boss.armor ? 1 : player.damage - boss.armor;
        unsigned netBossDmg = boss.damage <= player.armor ? 1 : boss.damage - player.armor;

        unsigned playerTurns = boss.hitPoints / netPlayerDmg + (boss.hitPoints % netPlayerDmg ? 1 : 0);
        unsigned bossTurns = player.hitPoints / netBossDmg + (player.hitPoints % netBossDmg ? 1 : 0);

        return bossTurns >= playerTurns;
    }
}


int main(int, char **)
{
    static const std::regex inputRegex("(.+): (\\d+)");
    Stats bossStats;

    std::string line;
    while (getline(std::cin, line))
    {
        std::smatch match;
        if (regex_match(line, match, inputRegex))
        {
            if (match[1] == "Hit Points")
                bossStats.hitPoints = stoul(match[2]);
            else if (match[1] == "Damage")
                bossStats.damage = stoul(match[2]);
            else if (match[1] == "Armor")
                bossStats.armor = stoul(match[2]);
            else
                std::cout << "Unknown attribute '" << match[1] << '\'' << std::endl;
        }
        else
            std::cout << "Could not parse line '" << line << '\'' << std::endl;
    }

    unsigned maxCost = 0, minCost = std::numeric_limits<unsigned>::max();

    for (const auto &weapon : weapons)
        for (const auto &armor : armors)
            for (const auto &ring1 : rings)
                for (const auto &ring2 : rings)
                {
                    if (&ring1 != &rings[0] && &ring1 == &ring2)
                        continue;

                    unsigned cost = weapon.cost + armor.cost + ring1.cost + ring2.cost;
                    unsigned damage = weapon.damage + armor.damage + ring1.damage + ring2.damage;
                    unsigned defence = weapon.armor + armor.armor + ring1.armor + ring2.armor;

                    if (simulateFight({ 100, damage, defence }, bossStats))
                        minCost = std::min(minCost, cost);
                    else
                        maxCost = std::max(maxCost, cost);
                }


    std::cout << "Minimum cost to win the fight: " << minCost << std::endl;
    std::cout << "Maximum cost to lose the fight: " << maxCost << std::endl;
}
