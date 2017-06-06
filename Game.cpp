#include "paddle.hpp"
#include "ball.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

void drawBackground(float x, float y, float z)
{
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);

	glTranslatef(x, y, z);
	glRotatef(0, 0, 0, 0);

	glBegin(GL_QUADS);

	glColor3f(0.0f, 1.0f, 0.0f);    
	glVertex3f(7.2f, 7.2f, -7.2f);    // Top Right Of The Quad (Top)
	glVertex3f(-7.2f, 7.2f, -7.2f);    // Top Left Of The Quad (Top)
	glVertex3f(-7.2f, 7.2f, 7.2f);    // Bottom Left Of The Quad (Top)
	glVertex3f(7.2f, 7.2f, 7.2f);    // Bottom Right Of The Quad (Top)

	glColor3f(1.0f, 1.0f, 0.0f);    
	glVertex3f(7.2f, -7.2f, 7.2f);    // Top Right Of The Quad (Bottom)
	glVertex3f(-7.2f, -7.2f, 7.2f);    // Top Left Of The Quad (Bottom)
	glVertex3f(-7.2f, -7.2f, -7.2f);    // Bottom Left Of The Quad (Bottom)
	glVertex3f(7.2f, -7.2f, -7.2f);    // Bottom Right Of The Quad (Bottom)

	glColor3f(0.0f, 0.7f, 0.0f);        
	glVertex3f(7.2f, 7.2f, 7.2f);    // Top Right Of The Quad (Front)
	glVertex3f(-7.2f, 7.2f, 7.2f);    // Top Left Of The Quad (Front)
	glVertex3f(-7.2f, -7.2f, 7.2f);    // Bottom Left Of The Quad (Front)
	glVertex3f(7.2f, -7.2f, 7.2f);    // Bottom Right Of The Quad (Front)

	glColor3f(1.0f, 1.0f, 0.0f);    
	glVertex3f(7.2f, -7.2f, -7.2f);    // Top Right Of The Quad (Back)
	glVertex3f(-7.2f, -7.2f, -7.2f);    // Top Left Of The Quad (Back)
	glVertex3f(-7.2f, 7.2f, -7.2f);    // Bottom Left Of The Quad (Back)
	glVertex3f(7.2f, 7.2f, -7.2f);    // Bottom Right Of The Quad (Back)

	glColor3f(0.0f, 0.0f, 1.0f);    
	glVertex3f(-7.2f, 7.2f, 7.2f);    // Top Right Of The Quad (Left)
	glVertex3f(-7.2f, 7.2f, -7.2f);    // Top Left Of The Quad (Left)
	glVertex3f(-7.2f, -7.2f, -7.2f);    // Bottom Left Of The Quad (Left)
	glVertex3f(-7.2f, -7.2f, 7.2f);    // Bottom Right Of The Quad (Left)

	glColor3f(1.0f, 0.0f, 1.0f);    
	glVertex3f(7.2f, 7.2f, -7.2f);    // Top Right Of The Quad (Right)
	glVertex3f(7.2f, 7.2f, 7.2f);    // Top Left Of The Quad (Right)
	glVertex3f(7.2f, -7.2f, 7.2f);    // Bottom Left Of The Quad (Right)
	glVertex3f(7.2f, -7.2f, -7.2f);  // Bottom Right Of The Quad (Right)

	glEnd();
	glPopMatrix();

}

void drawCube(float x, float y, float z)
{
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);
	
	glTranslatef(x, y, z);
	glRotatef(0, 0, 0, 0);
	
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
	// Make a window that is 900 x 900
	// And has the title "Pong"
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowWidth), "Pong!", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(24));
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	sf::ContextSettings settings = window.getSettings();
	
	std::cout << "Depth Bits:" << settings.depthBits << std::endl;
	std::cout << "Stencil Bits:" << settings.stencilBits << std::endl;
	std::cout << "Antialiasing Level:" << settings.antialiasingLevel << std::endl;
	std::cout << "Version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

	bool exitMode = false;

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Sounds/PaddleWoosh.wav"))
	{
		return -1;
	}

	sf::SoundBuffer buffer2;
	if (!buffer2.loadFromFile("Sounds/Goodbye.wav"))
	{
		return -1;
	}

	sf::Font font;
	if (!font.loadFromFile("Fonts/coolvetica rg.ttf"))
	{
		return -1;
	}

	sf::Sound sound;

	sf::Sound sound2;

	sound.setBuffer(buffer);

	sound2.setBuffer(buffer2);

	// activate the window
	window.setActive(true);

	int score = 0;
	int lives = 3;

	Paddle paddle(windowWidth / 2, windowHeight - 20);
	
	Ball ball(windowWidth / 2, 1);

	// load resources, initialize the OpenGL states, ...

	// run the main loop
	bool running = true;

	float counter = 0.0f;

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
			if (paddle.getPosition().left > -4.6)
			{
				std::cout << "Move Left" << std::endl;
				std::cout << "Paddle Position - Left: " << paddle.getPosition().left << std::endl;
				paddle.moveLeft();
				sound.play();
			}
		}

		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			if (paddle.getPosition().left < 4.6)
			{
				std::cout << "Move Right" << std::endl;
				std::cout << "Paddle Position - Right: " << paddle.getPosition().left << std::endl;
				paddle.moveRight();
				sound.play();
			}
		}
		
		else if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			std::cout << "Quit Game? Press Enter to leave" << std::endl;
			if (!exitMode)
			{
				sound2.play();
				exitMode = true;
			}
		}

		else if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			if (exitMode)
			{
				std::cout << "Exit" << std::endl;
				window.close();
				running = false;
			}
		}

		if (ball.getPosition().top > windowHeight)
		{
			ball.hitBottom();

			lives--;

			if (lives < 1) {
				window.close();
			}
		}

		ball.update();
		paddle.update(); 
		

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, 800.0f / 600.0f, 1.0f, 200.0f);
		
		drawCube(paddle.getPosition().left, -3, -9);
		drawCube(ball.getPosition().left, ball.getPosition().top, -13);
		if (ball.getPosition().left > 6.3 || ball.getPosition().left < -6.3)
		{
			float random = rand() % 201 + (-100);
			ball.flipXVelocity();
			ball.setYVelocity((float)(random / 1000));
		}
		if (ball.getPosition().top > 4.5)
		{
			ball.flipYVelocity();
		}
		if (ball.getPosition().top < -5)
		{
			ball.reset();
			ball.flipYVelocity();
		}
		drawBackground(0, 0, -20);

		counter += 0.1f;
		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...

	return 0;
}