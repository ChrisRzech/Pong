#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "PongLib/PongLib.hpp"

sf::Vector2f randDirection();

int main()
{
	srand(time(nullptr));

	/* Window settings */
	sf::Vector2u screenSize(400, 400);
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "Pong", sf::Style::Close);
	window.setFramerateLimit(60);

    /* Text */
    sf::Font textFont;
    if(!textFont.loadFromFile("resources/bit5x3.ttf"))
    {
        std::cout << "\"resources/bit5x3.ttf\" failed to load, aborting";
        return -1;
    }

    unsigned int p1Score = 0;
    unsigned int p2Score = 0;
    sf::Text p1TextScore(std::to_string(p1Score), textFont);
    sf::Text p2TextScore(std::to_string(p2Score), textFont);

    p1TextScore.setPosition(screenSize.x / 2 - p1TextScore.getCharacterSize(), 0);
    p2TextScore.setPosition(screenSize.x / 2 + p2TextScore.getCharacterSize(), 0);

	const sf::Vector2f paddleSize(10,50);
	const sf::Color entityColor = sf::Color::White;
	Pong::Paddle p1(sf::Vector2f(screenSize.x / 6, screenSize.y / 2 - paddleSize.y / 2), paddleSize, entityColor, 7);
	Pong::Paddle p2(sf::Vector2f(5 * screenSize.x / 6, screenSize.y / 2 - paddleSize.y / 2), paddleSize, entityColor, 7);
	Pong::Ball ball(static_cast<sf::Vector2f>(screenSize) / 2.f, 7, randDirection(), entityColor, 5);

	bool inputAllowed = true;

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
				inputAllowed = false;
				break;
			case sf::Event::GainedFocus:
				inputAllowed = true;
			default:
				break;
			}
		}

		/* Updating events */
        if(inputAllowed)
		{
        	/* Real-time input */
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) and p1.getPosition().y > 0)
				p1.move(Pong::Paddle::Direction::UP);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) and p1.getPosition().y + p1.getSize().y < screenSize.y)
				p1.move(Pong::Paddle::Direction::DOWN);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and p2.getPosition().y > 0)
				p2.move(Pong::Paddle::Direction::UP);

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and p2.getPosition().y + p2.getSize().y < screenSize.y)
				p2.move(Pong::Paddle::Direction::DOWN);

			/* Update ball */
			ball.update();
		}

		/* Collision logic */
		sf::FloatRect ballCollisionBox = ball.collisionBox();
		sf::FloatRect paddle1CollisionBox = p1.getCollisionBox();
		sf::FloatRect paddle2CollisionBox = p2.getCollisionBox();
		sf::Vector2f currDirection = ball.direction();

		if(ballCollisionBox.intersects(paddle1CollisionBox))
		{
			ball.setDirection({currDirection.x * -1, currDirection.y});
		}
		else if(ballCollisionBox.intersects(paddle2CollisionBox))
		{
			ball.setDirection({currDirection.x * -1, currDirection.y});
		}
		else if(ball.position().y < 0)
		{
			ball.setDirection({currDirection.x, currDirection.y * -1});
		}
		else if(ball.position().y + 2 * ball.radius() > screenSize.y)
		{
			ball.setDirection({currDirection.x, currDirection.y * -1});
		}
		else if(ball.position().x < 0)
		{
			p2Score++;
			p2TextScore.setString(std::to_string(p2Score));
			ball.setPosition(static_cast<sf::Vector2f>(screenSize) / 2.f);
			ball.setDirection(randDirection());
		}
		else if(ball.position().x > screenSize.x)
		{
			p1Score++;
			p1TextScore.setString(std::to_string(p1Score));
			ball.setPosition(static_cast<sf::Vector2f>(screenSize) / 2.f);
			ball.setDirection(randDirection());
		}

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
