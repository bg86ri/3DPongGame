#include "paddle.hpp"
#include "ball.hpp"
#include <sstream>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	GLdouble xmin, xmax, ymin, ymax;

	ymax = zNear * tan(fovy * 3.141592653 / 360.0);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;

	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);

}

void drawCube(float x, float y, float z)
{
	glMatrixMode(GL_PROJECTION);
	
	glTranslatef(x, y, z);
	glRotatef(0, 0, 0, 0);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glBegin(GL_QUADS);

	glColor3f(0.0f, 1.0f, 0.0f);    // Color Blue
	glVertex3f(0.5f, 0.5f, -0.5f);    // Top Right Of The Quad (Top)
	glVertex3f(-0.5f, 0.5f, -0.5f);    // Top Left Of The Quad (Top)
	glVertex3f(-0.5f, 0.5f, 0.5f);    // Bottom Left Of The Quad (Top)
	glVertex3f(0.5f, 0.5f, 0.5f);    // Bottom Right Of The Quad (Top)
	
	glColor3f(1.0f, 1.0f, 0.0f);    // Color Orange
	glVertex3f(0.5f, -0.5f, 0.5f);    // Top Right Of The Quad (Bottom)
	glVertex3f(-0.5f, -0.5f, 0.5f);    // Top Left Of The Quad (Bottom)
	glVertex3f(-0.5f, -0.5f, -0.5f);    // Bottom Left Of The Quad (Bottom)
	glVertex3f(0.5f, -0.5f, -0.5f);    // Bottom Right Of The Quad (Bottom)
	
	glColor3f(1.0f, 0.0f, 0.0f);    // Color Red    
	glVertex3f(0.5f, 0.5f, 0.5f);    // Top Right Of The Quad (Front)
	glVertex3f(-0.5f, 0.5f, 0.5f);    // Top Left Of The Quad (Front)
	glVertex3f(-0.5f, -0.5f, 0.5f);    // Bottom Left Of The Quad (Front)
	glVertex3f(0.5f, -0.5f, 0.5f);    // Bottom Right Of The Quad (Front)
	
	glColor3f(1.0f, 1.0f, 0.0f);    // Color Yellow
	glVertex3f(0.5f, -0.5f, -0.5f);    // Top Right Of The Quad (Back)
	glVertex3f(-0.5f, -0.5f, -0.5f);    // Top Left Of The Quad (Back)
	glVertex3f(-0.5f, 0.5f, -0.5f);    // Bottom Left Of The Quad (Back)
	glVertex3f(0.5f, 0.5f, -0.5f);    // Bottom Right Of The Quad (Back)
	
	glColor3f(0.0f, 0.0f, 1.0f);    // Color Blue
	glVertex3f(-0.5f, 0.5f, 0.5f);    // Top Right Of The Quad (Left)
	glVertex3f(-0.5f, 0.5f, -0.5f);    // Top Left Of The Quad (Left)
	glVertex3f(-0.5f, -0.5f, -0.5f);    // Bottom Left Of The Quad (Left)
	glVertex3f(-0.5f, -0.5f, 0.5f);    // Bottom Right Of The Quad (Left)
	
	glColor3f(1.0f, 0.0f, 1.0f);    // Color Violet
	glVertex3f(0.5f, 0.5f, -0.5f);    // Top Right Of The Quad (Right)
	glVertex3f(0.5f, 0.5f, 0.5f);    // Top Left Of The Quad (Right)
	glVertex3f(0.5f, -0.5f, 0.5f);    // Bottom Left Of The Quad (Right)
	glVertex3f(0.5f, -0.5f, -0.5f);  // Bottom Right Of The Quad (Right)

	glEnd();
	glPopMatrix();
}

int main()
{
	// create the window
	int windowWidth = 900;
	int windowHeight = 900;
	// Make a window that is 1024 by 768 pixels
	// And has the title "Pong"
	//RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");
	sf::Window window(sf::VideoMode(windowWidth, windowWidth), "Pong!", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(24));
	window.setVerticalSyncEnabled(true);

	// activate the window
	window.setActive(true);

	int score = 0;
	int lives = 3;

	Paddle paddle(windowWidth / 2, windowHeight - 20);
	
	Ball ball(windowWidth / 2, 1);

	Text hud;
	
	Font font;
	font.loadFromFile("coolvetica rg.ttf");

	hud.setFont(font);

	hud.setCharacterSize(75);

	hud.setFillColor(sf::Color::Red);

	// load resources, initialize the OpenGL states, ...

	// run the main loop
	bool running = true;
	while (running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			paddle.moveLeft();
		}

		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			paddle.moveRight();
		}

		else if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (ball.getPosition().top > windowHeight)
		{
			ball.hitBottom();

			lives--;

			if (lives < 1) {
				window.close();
			}
		}

		if (ball.getPosition().top < 0)
		{
			ball.reboundPaddleOrTop();
			score++;
		}

		if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth)
		{
			ball.reboundSides();
		}

		if (ball.getPosition().intersects(paddle.getPosition()))
		{
			ball.reboundPaddleOrTop();
		}

		ball.update();
		paddle.update();

		std::stringstream ss;
		ss << "Score:" << score << "      Lives:" << lives;
		hud.setString(ss.str());

		//window.clear(Color(26, 128, 182, 255));
		//window.draw(ball.getShape());
		//window.draw(hud);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, 800.0f / 600.0f, 1.0f, 200.0f);
		
		drawCube(paddle.getPosition().left, -3, -10);
		drawCube(0, 5, -10);
		//drawCube(0, 5, -10);
		drawCube(0, 5, -10);

		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}