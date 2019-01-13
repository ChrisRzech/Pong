#include "Ball.hpp"

namespace Pong
{
/* Constructors */
Ball::Ball(const sf::Vector2f& POS, float radius, sf::Color color, float speed)
    : m_circle(radius), m_speed(speed)
{
    m_circle.setPosition(POS);
    m_circle.setFillColor(color);
}

/* Getters */
sf::FloatRect Ball::getCollisionBox() const
{
    return m_circle.getGlobalBounds();
}

sf::Vector2f Ball::getPosition() const
{
    return m_circle.getPosition();
}

sf::Vector2f Ball::getDirection() const
{
    return m_direction;
}

sf::Color Ball::getColor() const
{
    return m_circle.getFillColor();
}

float Ball::getRadius() const
{
    return m_circle.getRadius();
}

float Ball::getSpeed() const
{
    return m_speed;
}

/* Setters */
void Ball::setPosition(sf::Vector2f v)
{
    m_circle.setPosition(v);
}

void Ball::setDirection(sf::Vector2f v)
{
    m_direction = v;
}

void Ball::setColor(sf::Color v)
{
    m_circle.setFillColor(v);
}

void Ball::setRadius(float v)
{
    m_circle.setRadius(v);
}

void Ball::setSpeed(float v)
{
    m_speed = v;
}

/* Updaters */
void Ball::draw(sf::RenderWindow& w) const
{
    w.draw(m_circle);
}

void Ball::update()
{
    float dirMag = std::hypot(m_direction.x, m_direction.y);
    sf::Vector2f unitVec(m_direction / dirMag);

    m_circle.move(unitVec * m_speed);
}
}
