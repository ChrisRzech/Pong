#pragma once
#include <SFML/Graphics.hpp>

namespace Pong
{
class Paddle
{
public:
	enum class Direction {UP = -1, STOP = 0, DOWN = 1};

	/* Constructors */
	Paddle(const sf::Vector2f& pos, const sf::Vector2f& size, sf::Color, float speed);

	/* Getters */
	sf::FloatRect getCollisionBox() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	sf::Color getColor() const;
	float getSpeed() const;

	/* Setters */
	void setPosition(const sf::Vector2f&);
	void setSize(const sf::Vector2f&);
	void setColor(sf::Color);
	void setSpeed(float);

	/* Movement */
	void move(Direction);

	/* Render */
	void draw(sf::RenderWindow&) const;

private:
	sf::RectangleShape m_block;
	float m_speed;
};
}
