#include <cstdlib>
#include <ctime>
#include <SFML/System/Vector2.hpp>

sf::Vector2f randDirection()
{
	float xVec = rand() % 100 + 1;
	float yVec = rand() % 5 + 1;
	int xDir = rand() % 2;
	int yDir = rand() % 2;

	return sf::Vector2f(xDir? -1 * xVec : xVec, yDir? -1 * yVec : yVec);
}
