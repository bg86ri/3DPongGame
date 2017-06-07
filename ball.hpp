#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
	Vector2f position;
	RectangleShape ballShape;
	float xVelocity = .1f;
	float yVelocity = .01f;

public:
	Ball(float startX, float startY);
	FloatRect getPosition();
	void setYVelocity(float pRand);
	float getXVelocity();
	float getYVelocity();
	void update();
	void flipXVelocity();
	void flipYVelocity();
	void reset();
};