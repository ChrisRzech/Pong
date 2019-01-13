#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

namespace Pong
{
class Ball
{
public:
    /* Constructors */
    Ball(const sf::Vector2f& pos, float radius, sf::Color, float speed);

    /* Getters */
    sf::FloatRect getCollisionBox() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getDirection() const;
    sf::Color getColor() const;
    float getRadius() const;
    float getSpeed() const;

    /* Setters */
    void setPosition(sf::Vector2f);
    void setDirection(sf::Vector2f);
    void setColor(sf::Color);
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
