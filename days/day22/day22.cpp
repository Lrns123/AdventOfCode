#include <iostream>
#include <regex>

void simulate(bool playerTurn, int bossHP, int bossDamage, int playerHP, unsigned playerMana, unsigned shieldTicks, unsigned poisonTicks, unsigned rechargeTicks, unsigned manaSpent, bool hardMode, unsigned &lowestManaCost)
{
    if (manaSpent > lowestManaCost)
        return;

    if (hardMode && playerTurn && (playerHP -= 1) <= 0)
        return;

    int playerArmor = shieldTicks ? 7 : 0;

    // Apply effects
    if (shieldTicks)   --shieldTicks;
    if (poisonTicks)   --poisonTicks,   bossHP -= 3;
    if (rechargeTicks) --rechargeTicks, playerMana += 101;

    if (bossHP <= 0) // Boss defeated
    {
        lowestManaCost = std::min(lowestManaCost, manaSpent);
        return;
    }

    if (!playerTurn)
    {
        playerHP -= std::max(1, bossDamage - playerArmor);
        if (playerHP > 0)
            simulate(!playerTurn, bossHP, bossDamage, playerHP, playerMana, shieldTicks, poisonTicks, rechargeTicks, manaSpent, hardMode, lowestManaCost);
    }
    else
    {
        // Recurse through all viable attacks
        if (playerMana >= 53)  // Magic Missile
            simulate(!playerTurn, bossHP - 4, bossDamage, playerHP, playerMana - 53, shieldTicks, poisonTicks, rechargeTicks, manaSpent + 53, hardMode, lowestManaCost);

        if (playerMana >= 73) // Drain
            simulate(!playerTurn, bossHP - 2, bossDamage, playerHP + 2, playerMana - 73, shieldTicks, poisonTicks, rechargeTicks, manaSpent + 73, hardMode, lowestManaCost);

        if (playerMana >= 113 && !shieldTicks) // Shield
            simulate(!playerTurn, bossHP, bossDamage, playerHP, playerMana - 113, 6, poisonTicks, rechargeTicks, manaSpent + 113, hardMode, lowestManaCost);

        if (playerMana >= 173 && !poisonTicks) // Poison
            simulate(!playerTurn, bossHP, bossDamage, playerHP, playerMana - 173, shieldTicks, 6, rechargeTicks, manaSpent + 173, hardMode, lowestManaCost);

        if (playerMana >= 229 && !rechargeTicks) // Recharge
            simulate(!playerTurn, bossHP, bossDamage, playerHP, playerMana - 229, shieldTicks, poisonTicks, 5, manaSpent + 229, hardMode, lowestManaCost);
    }
}

int main(int, char **)
{
    static const std::regex inputRegex("(.+): (\\d+)");
    unsigned bossHP = 0, bossDamage = 0;

    std::string line;
    while (getline(std::cin, line))
    {
        std::smatch match;
        if (regex_match(line, match, inputRegex))
        {
            if (match[1] == "Hit Points")
                bossHP = stoul(match[2]);
            else if (match[1] == "Damage")
                bossDamage = stoul(match[2]);
            else
                std::cout << "Unknown attribute '" << match[1] << '\'' << std::endl;
        }
        else
            std::cout << "Could not parse line '" << line << '\'' << std::endl;
    }

    unsigned easy, hard = std::numeric_limits<unsigned>::max();
    simulate(true, bossHP, bossDamage, 50, 500, 0, 0, 0, 0, false, easy);
    simulate(true, bossHP, bossDamage, 50, 500, 0, 0, 0, 0, true, hard);

    std::cout << "Minimum mana required to win (easy): " << easy << std::endl;
    std::cout << "Minimum mana required to win (hard): " << hard << std::endl;
}
