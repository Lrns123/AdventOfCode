#include <map>
#include <regex>
#include <iostream>

struct Ingredient
{
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
};

bool nextCombination(std::vector<int> &separators)
{
    size_t idx = separators.size();
    bool checkConsecutive = false;

    while (idx--)
    {
        if (separators[idx]++ == 100)
        {
            if (idx == 0)
                return false;

            separators[idx] = 0;
            checkConsecutive = true;
        }
        else
            break;
    }

    if (!checkConsecutive)
        return true;

    // Ensure all separators are consecutive
    int lowest = 0;
    for (int & val : separators)
    {
        if (val < lowest)
            val = lowest;

        lowest = val;
    }

    return true;
}

void getQuantities(std::vector<int> &quantities, const std::vector<int> &separators)
{    
    quantities.front() = separators.front();
    for (size_t i = 1; i < separators.size(); ++i)
        quantities[i] = separators[i] - separators[i - 1];
    
    quantities.back() = 100 - separators.back();
}

long long getScore(const std::vector<Ingredient> &ingredients, const std::vector<int> &quantities)
{
    int capacity = 0, durability = 0, flavor = 0, texture = 0;
    size_t n = ingredients.size();

    for (size_t i = 0; i != n; ++i)
    {
        capacity += ingredients[i].capacity * quantities[i];
        durability += ingredients[i].durability * quantities[i];
        flavor += ingredients[i].flavor * quantities[i];
        texture += ingredients[i].texture * quantities[i];
    }

    if (capacity <= 0 || durability <= 0 || flavor <= 0 || texture <= 0)
        return 0;

    return capacity * durability * flavor * texture;
}

int getCalories(const std::vector<Ingredient> &ingredients, const std::vector<int> &quantities)
{
    int calories = 0;
 
    for (size_t i = 0, n = ingredients.size(); i != n; ++i)
        calories += ingredients[i].calories * quantities[i];

    return calories;
}


void findBestScore(const std::vector<Ingredient> &ingredients, long long &bestScore, long long &bestScoreWithCalories)
{
    bestScore = 0;
    bestScoreWithCalories = 0;

    std::vector<int> quantities(ingredients.size());
    std::vector<int> separators(ingredients.size() - 1);

    do
    {
        getQuantities(quantities, separators);
        long long score = getScore(ingredients, quantities);
        if (score > bestScore)
            bestScore = score;

        if (score > bestScoreWithCalories && getCalories(ingredients, quantities) == 500)
            bestScoreWithCalories = score;
        
    } while (nextCombination(separators)); 
}

int main(int, char**)
{
    static std::regex inputRegex("\\w+: capacity (-?\\d+), durability (-?\\d+), flavor (-?\\d+), texture (-?\\d+), calories (-?\\d+)");
    std::vector<Ingredient> ingredients;
    
    std::string input;
    std::smatch match;
    while (getline(std::cin, input))
    {    
        if (regex_match(input, match, inputRegex))
            ingredients.emplace_back(Ingredient{ stoi(match[2].str()), stoi(match[3].str()), stoi(match[4].str()), stoi(match[5].str()), stoi(match[6].str()) });
        else
            std::cout << "Cannot parse line '" << input << '\'' << std::endl;
    }

    long long bestScore, bestScoreWithCalories;
    findBestScore(ingredients, bestScore, bestScoreWithCalories);

    std::cout << "Best total score: " << bestScore << std::endl;
    std::cout << "Best total score with 500 calories: " << bestScoreWithCalories << std::endl;
}