#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <atomic>
#include <mutex>
#include <thread>

#include "md5.hpp"

static void findHash(const std::string &key, int &first, int &second)
{
    static std::atomic<int> nextNumber = 0;
    static std::atomic<bool> finished = false;
    static std::mutex mutex;

    while (!finished)
    {
        size_t number = nextNumber++;

        std::ostringstream stream;
        stream << key << number;

        auto data = stream.str();
        auto hash = MD5().update(data).final();

        if (hash[0] == 0 && hash[1] == 0 && hash[2] >> 4 == 0)
        {
            std::lock_guard<std::mutex> lock(mutex);

            if (first == -1)
                first = number;

            if (hash[2] == 0 && second == -1)
            {
                second = number;
                finished = true;    // Finding a match with 6 leading zeroes implies a match with 5 zeroes must also have been found.
            }
        }
    }
}

int main(int, char **)
{
    int matches[2] = { -1, -1 };
    std::string key;
    std::cin >> key;

    std::vector<std::thread> threads;
    
    for (size_t i = 0, n = std::thread::hardware_concurrency(); i != n; ++i)
        threads.emplace_back(findHash, std::cref(key), std::ref(matches[0]), std::ref(matches[1]));
    
    for (auto &thread : threads)
        thread.join();

    std::cout << "First with 5 zeroes: " << matches[0] << std::endl;
    std::cout << "First with 6 zeroes: " << matches[1] << std::endl;
}