#include "Ball.hpp"

namespace Pong
{
/* Constructors */
Ball::Ball(const sf::Vector2f& POS, float radius, const sf::Vector2f& DIRECTION, const sf::Color& COLOR, float speed)
	: m_circle(radius), m_direction(DIRECTION), m_speed(speed)
{
	m_circle.setPosition(POS);
	m_circle.setFillColor(COLOR);
}

/* Getters */
sf::FloatRect Ball::collisionBox() const {return m_circle.getGlobalBounds();}
sf::Vector2f  Ball::position()     const {return m_circle.getPosition();}
sf::Vector2f  Ball::direction()    const {return m_direction;}
sf::Color     Ball::color()        const {return m_circle.getFillColor();}
float         Ball::radius()       const {return m_circle.getRadius();}
float         Ball::speed()        const {return m_speed;}

/* Setters */
void Ball::setPosition (const sf::Vector2f& v) {m_circle.setPosition(v);}
void Ball::setDirection(const sf::Vector2f& v) {m_direction = v;}
void Ball::setColor    (const sf::Color& v)    {m_circle.setFillColor(v);}
void Ball::setRadius   (float v)               {m_circle.setRadius(v);}
void Ball::setSpeed    (float v)               {m_speed = v;}

/* Updaters */
void Ball::draw(sf::RenderWindow& w) const {w.draw(m_circle);}

void Ball::update()
{
	float directionMagnitude = std::hypot(m_direction.x, m_direction.y);
	sf::Vector2f unitVec(m_direction / directionMagnitude);

	m_circle.move(unitVec * m_speed);
}
}
