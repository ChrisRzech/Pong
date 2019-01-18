#include <cstdlib>
#include <cmath>
#include <SFML/System/Vector2.hpp>

sf::Vector2f randDirection(int minDeg, int maxDeg)
{
    int randDeg = (rand() % (maxDeg - minDeg)) + minDeg;
    float x = std::cos(randDeg * static_cast<float>(M_PI) / 180);
    float y = std::sin(randDeg * static_cast<float>(M_PI) / 180);

    //Since y axis grows down, we must flip the y result
    y *= -1;

    return sf::Vector2f(x, y);
}
