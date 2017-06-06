#include "ball.hpp"

Ball::Ball(float startX, float startY)
{
	position.x = 0;
	position.y = 0;

	ballShape.setSize(sf::Vector2f(10, 10));
	ballShape.setPosition(position);
}

FloatRect Ball::getPosition()
{
	return ballShape.getGlobalBounds();
}

RectangleShape Ball::getShape()
{
	return ballShape;
}

float Ball::getXVelocity()
{
	return xVelocity;
}

void Ball::setYVelocity(float pRand)
{
	yVelocity = pRand;
}

float Ball::getYVelocity()
{
	return yVelocity;
}

void Ball::hitBottom()
{
	position.y = 1;
	position.x = 500;
}

void Ball::update()
{
	position.y += yVelocity;
	position.x += xVelocity;

	ballShape.setPosition(position);
}

void Ball::flipXVelocity()
{
	if (xVelocity < 0)
	{
		xVelocity = 0.1f;
	}
	else if (xVelocity > 0)
	{
		xVelocity = -0.1f;
	}
}

void Ball::flipYVelocity()
{
	if (yVelocity < 0)
	{
		yVelocity = 0.1f;
	}
	else if (yVelocity > 0)
	{
		yVelocity = -0.1f;
	}
}

void Ball::reset()
{
	this->position.x = 0;
	this->position.y = 0;
}