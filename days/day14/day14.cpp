#include <map>
#include <regex>
#include <iostream>

struct ReindeerInfo
{
    size_t speed;
    size_t runTime;
    size_t restTime;
};

size_t calculateDistance(const ReindeerInfo &info, size_t duration)
{
    size_t blockLength = info.runTime + info.restTime;
    size_t blocks = duration / blockLength;
    size_t remainder = duration % blockLength;

    size_t distance = blocks * info.speed * info.runTime;

    if (remainder < info.runTime)
        distance += info.speed * remainder;
    else
        distance += info.speed * info.runTime;

    return distance;
}

std::map<std::string, size_t> simulateRace(const std::map<std::string, ReindeerInfo> &map, size_t duration)
{
    struct SimulatedReindeer
    {
        std::string name;
        ReindeerInfo info;
        size_t distance;
        size_t points;
        size_t time;

        // This should be more efficient than repeatedly calling calculateDistance.
        size_t advance()
        {
            return time++ % (info.runTime + info.restTime) < info.runTime ? distance += info.speed : distance;
        }
    };

    std::map<std::string, size_t> ret;

    std::vector<SimulatedReindeer> reindeerList;
    for (const auto &reindeer : map)
        reindeerList.emplace_back(SimulatedReindeer{ reindeer.first, reindeer.second, 0, 0, 0 });

    for (size_t time = 0; time != duration; ++time)
    {
        size_t maxDistance = 0;
        for (auto &reindeer : reindeerList)
            maxDistance = std::max(maxDistance, reindeer.advance());
        
        for (auto &reindeer : reindeerList)
            if (reindeer.distance == maxDistance)
                ++reindeer.points;
    }

    for (auto &reindeer : reindeerList)
        ret.emplace(reindeer.name, reindeer.points);

    return ret;
}

int main(int, char**)
{
    static const std::regex inputRegex("(\\w+) can fly (\\d+) km/s for (\\d+) seconds, but then must rest for (\\d+) seconds.");
    std::map<std::string, ReindeerInfo> reindeerMap;
    
    std::string input;
    while (getline(std::cin, input))
    {    
        std::smatch match;
        if (regex_match(input, match, inputRegex))
            reindeerMap.emplace(match[1].str(), ReindeerInfo{ stoul(match[2].str()), stoul(match[3].str()), stoul(match[4].str()) });
        else
            std::cout << "Cannot parse line '" << input << '\'' << std::endl;
    }

    size_t maxDistance = 0;
    for (const auto &reindeer : reindeerMap)
        maxDistance = std::max(maxDistance, calculateDistance(reindeer.second, 2503));

    std::cout << "Distance ran by winning reindeer: " << maxDistance << std::endl;

    auto result = simulateRace(reindeerMap, 2503);
    auto maxScore = std::max_element(result.begin(), result.end(), [](const auto &p1, const auto &p2) { return p1.second < p2.second; })->second;

    std::cout << "Points obtained by winning reindeer: " << maxScore << std::endl;
}