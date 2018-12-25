#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

namespace Pong
{
class Ball
{
public:
	/* Constructors */
	Ball(const sf::Vector2f& position, float radius, const sf::Vector2f& direction, const sf::Color&, float speed);

	/* Getters */
	sf::FloatRect collisionBox() const;
	sf::Vector2f position() const;
	sf::Vector2f direction() const;
	sf::Color color() const;
	float radius() const;
	float speed() const;

	/* Setters */
	void setPosition(const sf::Vector2f&);
	void setDirection(const sf::Vector2f&);
	void setColor(const sf::Color&);
	void setRadius(float);
	void setSpeed(float);

	/* Updaters */
	void draw(sf::RenderWindow&) const;
	void update();

private:
	sf::CircleShape m_circle;
	sf::Vector2f m_direction;
	float m_speed;
};
}
