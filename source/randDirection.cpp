#include <random>
#include <chrono>
#include <cmath>
#include <SFML/System/Vector2.hpp>

sf::Vector2f randDirection(int minDeg, int maxDeg)
{
    static unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine randEng(seed);
    std::uniform_int_distribution<int> rand(minDeg, maxDeg);

    int randDeg = rand(randEng);
    float x = std::cos(randDeg * static_cast<float>(M_PI) / 180);
    float y = std::sin(randDeg * static_cast<float>(M_PI) / 180);

    //Since y axis grows down, we must flip the y result
    return {x, -1 * y};
}