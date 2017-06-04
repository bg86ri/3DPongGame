#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Paddle
{
private:
	
	RectangleShape paddleShape;
	float paddleSpeed = .3f;

public:
	Paddle(float startX, float startY);
	FloatRect getPosition();
	Vector2f position;
	RectangleShape getShape();
	void moveLeft();
	void moveRight();
	void update();
};