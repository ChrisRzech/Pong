#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "PongLib/PongLib.hpp"

sf::Vector2f randDirection(int minDeg, int maxDeg);

int main()
{
    /* Window icon */
    sf::Image icon;
    if(!icon.loadFromFile("resources/icon.png"))
    {
        std::cerr << "\"resources/icon.png\" failed to load, aborting";
        return -1;
    }

    /* Window settings */
    const sf::Vector2u SCREEN_SIZE(450, 300);
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "Pong", sf::Style::Close);
    window.setFramerateLimit(60);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    /* Text */
    sf::Font textFont;
    if(!textFont.loadFromFile("resources/bit5x3.ttf"))
    {
        std::cerr << "\"resources/bit5x3.ttf\" failed to load, aborting";
        return -1;
    }

    sf::Text p1TextScore("", textFont);
    sf::Text p2TextScore("", textFont);

    p1TextScore.setPosition(0, 0);
    p2TextScore.setPosition(SCREEN_SIZE.x - p2TextScore.getCharacterSize(), 0);

    /* Score */
    unsigned int p1Score = 0;
    unsigned int p2Score = 0;

    /* Gamepieces */
    const sf::Color ENTITY_COLOR = sf::Color::White;
    const sf::Vector2f PADDLE_SIZE(10, 50);

    const sf::Vector2f P1_INITIAL_POS(SCREEN_SIZE.x / 6, SCREEN_SIZE.y / 2 - PADDLE_SIZE.y / 2);
    const sf::Vector2f P2_INITIAL_POS(5 * SCREEN_SIZE.x / 6, SCREEN_SIZE.y / 2 - PADDLE_SIZE.y / 2);
    const sf::Vector2f BALL_INITIAL_POS(static_cast<sf::Vector2f>(SCREEN_SIZE) / 2.f);
    const int MIN_RAND_DEG = -45;
    const int MAX_RAND_DEG = 45;

    Pong::Paddle p1(P1_INITIAL_POS, PADDLE_SIZE, ENTITY_COLOR, 7);
    Pong::Paddle p2(P2_INITIAL_POS, PADDLE_SIZE, ENTITY_COLOR, 7);
    Pong::Ball ball(BALL_INITIAL_POS, 7, ENTITY_COLOR, 6);
    ball.setDirection(randDirection(MIN_RAND_DEG, MAX_RAND_DEG));

    /* Game flags */
    bool paused = false;

    /* Window loop */
    while(window.isOpen())
    {
        /* Events */
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::LostFocus:
                paused = true;
                break;
            case sf::Event::GainedFocus:
                paused = false;
            default:
                break;
            }
        }

        /* Updating events */
        if(!paused)
        {
            /* Realtime input */
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                p1.move(Pong::Paddle::Direction::UP);

                //Move to valid position if out-of-bounds
                if(p1.getPosition().y < 0)
                    p1.setPosition(sf::Vector2f(p1.getPosition().x, 0));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                p1.move(Pong::Paddle::Direction::DOWN);

                //Move to valid position if out-of-bounds
                if(p1.getPosition().y + p1.getSize().y >= SCREEN_SIZE.y)
                    p1.setPosition(sf::Vector2f(p1.getPosition().x, SCREEN_SIZE.y - p1.getSize().y));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                p2.move(Pong::Paddle::Direction::UP);

                //Move to valid position if out-of-bounds
                if(p2.getPosition().y < 0)
                    p2.setPosition(sf::Vector2f(p2.getPosition().x, 0));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                p2.move(Pong::Paddle::Direction::DOWN);

                //Move to valid position if out-of-bounds
                if(p2.getPosition().y + p2.getSize().y >= SCREEN_SIZE.y)
                    p2.setPosition(sf::Vector2f(p2.getPosition().x, SCREEN_SIZE.y - p2.getSize().y));
            }

            /* Update ball */
            ball.update();
        }

        /* Collision logic */
        sf::FloatRect ballCollisionBox = ball.getCollisionBox();
        sf::FloatRect paddle1CollisionBox = p1.getCollisionBox();
        sf::FloatRect paddle2CollisionBox = p2.getCollisionBox();
        sf::Vector2f currDirection = ball.getDirection();

        if(ballCollisionBox.intersects(paddle1CollisionBox))
        {
            ball.setDirection(randDirection(MIN_RAND_DEG, MAX_RAND_DEG));
        }
        else if(ballCollisionBox.intersects(paddle2CollisionBox))
        {
            ball.setDirection(randDirection(MIN_RAND_DEG + 180, MAX_RAND_DEG + 180));
        }
        else if(ball.getPosition().y < 0)
        {
            sf::Vector2f ballPos = ball.getPosition();
            ball.setPosition(sf::Vector2f(ballPos.x, 0));
            ball.setDirection({currDirection.x, currDirection.y * -1});
        }
        else if(ball.getPosition().y + 2 * ball.getRadius() > SCREEN_SIZE.y)
        {
            sf::Vector2f ballPos = ball.getPosition();
            ball.setPosition(sf::Vector2f(ballPos.x, SCREEN_SIZE.y - 2 * ball.getRadius()));
            ball.setDirection({currDirection.x, currDirection.y * -1});
        }
        else if(ball.getPosition().x < 0)
        {
            p2Score++;
            p2TextScore.setString(std::to_string(p2Score));
            ball.setPosition(BALL_INITIAL_POS);
            ball.setDirection(randDirection(MIN_RAND_DEG, MAX_RAND_DEG));
        }
        else if(ball.getPosition().x > SCREEN_SIZE.x)
        {
            p1Score++;
            p1TextScore.setString(std::to_string(p1Score));
            ball.setPosition(BALL_INITIAL_POS);
            ball.setDirection(randDirection(MIN_RAND_DEG + 180, MAX_RAND_DEG + 180));
        }

        /* Text updates */
        p1TextScore.setString(std::to_string(p1Score));
        p2TextScore.setString(std::to_string(p2Score));

        /* Rendering */
        window.clear(sf::Color::Black);
        window.draw(p1TextScore);
        window.draw(p2TextScore);
        p1.draw(window);
        p2.draw(window);
        ball.draw(window);
        window.display();
    }
}
