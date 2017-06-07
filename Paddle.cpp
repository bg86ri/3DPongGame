#include "paddle.hpp"

//this sets the paddles attributes
Paddle::Paddle(float x, float y)
{
	position.x = 0;
	position.y = 2000;

	paddleShape.setSize(sf::Vector2f(50, 5));
	paddleShape.setPosition(position);
}	

//this uses the shapes global bounds to find out the position
FloatRect Paddle::getPosition()
	{
		return paddleShape.getGlobalBounds();
	}

//this takes the paddle speed (set in paddle.hpp) to move the paddle on the x axis to the left
void Paddle::moveLeft()
{
	position.x -= paddleSpeed;
}

//this takes the paddle speed (set in paddle.hpp) to move the paddle on the x axis to the right
void Paddle::moveRight()
{
	position.x += paddleSpeed;
}

//when the paddle updates it will update where the paddle is on screen
void Paddle::update()
{
	paddleShape.setPosition(position);
}