#include "ball.hpp"

//this sets all the ball's starting attributes
Ball::Ball(float startX, float startY)
{
	position.x = 0;
	position.y = 0;

	ballShape.setSize(sf::Vector2f(10, 10));
	ballShape.setPosition(position);
}

//this obtains the balls position using the balls global bounds
FloatRect Ball::getPosition()
{
	return ballShape.getGlobalBounds();
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

//this will change the position of the ball based on the velocity
void Ball::update()
{
	position.y += yVelocity;
	position.x += xVelocity;

	ballShape.setPosition(position);
}

//this changes the direction that the ball is travelling on the Y axis when called
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

//this changes the direction that the ball is travelling on the Y axis when called
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

//when this will put the ball back in the center of the screen when called
void Ball::reset()
{
	this->position.x = 0;
	this->position.y = 0;
}