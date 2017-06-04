#include "paddle.hpp"

Paddle::Paddle(float startX, float startY)
{
	position.x = 0;
	position.y = 2000;

	paddleShape.setSize(sf::Vector2f(50, 5));
	paddleShape.setPosition(position);
}	

FloatRect Paddle::getPosition()
	{
		return paddleShape.getGlobalBounds();
	}

RectangleShape Paddle::getShape()
	{
		return paddleShape;
	}

void Paddle::moveLeft()
{
	position.x -= paddleSpeed;
}

void Paddle::moveRight()
{
	position.x += paddleSpeed;
}

void Paddle::update()
{
	paddleShape.setPosition(position);
}