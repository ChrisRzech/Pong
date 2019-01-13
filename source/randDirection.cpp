#include <cstdlib>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include "PongLib/Ball/Ball.hpp"

sf::Vector2f randDirection(int maxGoodDeg, int minGoodDeg)
{
    int randDeg = (rand() % (maxGoodDeg - minGoodDeg)) + minGoodDeg;
    float x = std::cos(randDeg * static_cast<float>(M_PI) / 180);
    float y = std::sin(randDeg * static_cast<float>(M_PI) / 180);
    bool xFlip = rand() % 2 == 0; //Asking if it's even so it makes sense
    bool yFlip = rand() % 2 == 0;

    return sf::Vector2f(xFlip ? -1 * x : x, yFlip ? -1 * y : y);
}
