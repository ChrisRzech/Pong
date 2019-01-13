#include "Paddle.hpp"

namespace Pong
{
/* Constructors */
Paddle::Paddle(const sf::Vector2f& POS, const sf::Vector2f& SIZE, sf::Color color, float speed)
      : m_block(SIZE), m_speed(speed)
{
    m_block.setPosition(POS);
    m_block.setFillColor(color);
}

/* Getters */
sf::FloatRect Paddle::getCollisionBox() const
{
    return m_block.getGlobalBounds();
}

sf::Vector2f Paddle::getPosition() const
{
    return m_block.getPosition();
}

sf::Vector2f Paddle::getSize() const
{
    return m_block.getSize();
}

sf::Color Paddle::getColor() const
{
    return m_block.getFillColor();
}

float Paddle::getSpeed() const
{
    return m_speed;
}

/* Setters */
void Paddle::setPosition(sf::Vector2f v)
{
    m_block.setPosition(v);
}

void Paddle::setSize(sf::Vector2f v)
{
    m_block.setSize(v);
}

void Paddle::setColor(sf::Color v)
{
    m_block.setFillColor(v);
}

void Paddle::setSpeed(float v)
{
    m_speed = v;
}

/* Movement */
void Paddle::move(Direction dir)
{
    m_block.move(0, static_cast<int>(dir) * m_speed);
}

/* Render */
void Paddle::draw(sf::RenderWindow& window) const
{
    window.draw(m_block);
}
}
