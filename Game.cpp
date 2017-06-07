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

//this initialises the camera aspect ratios, etc
void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	GLdouble xmin, xmax, ymin, ymax;

	ymax = zNear * tan(fovy * 3.141592653 / 360.0);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;

	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);

}

//this draws the background
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

//this draws both the paddle and the ball
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

	//this determines whether enter will exit the game or not
	bool exitMode = false;

	//these load in the sounds to be used
	sf::SoundBuffer PMBuffer;
	if (!PMBuffer.loadFromFile("Sounds/PaddleWoosh.wav"))
	{
		return -1;
	}

	sf::SoundBuffer ByeBuffer;
	if (!ByeBuffer.loadFromFile("Sounds/Goodbye.wav"))
	{
		return -1;
	}

	sf::SoundBuffer BHBuffer;
	if (!BHBuffer.loadFromFile("Sounds/BallBounce.wav"))
	{
		return -1;
	}

	//this allows me to use the sounds
	sf::Sound PaddleMove;

	sf::Sound Bye;

	sf::Sound BallHit;

	PaddleMove.setBuffer(PMBuffer);

	Bye.setBuffer(ByeBuffer);

	BallHit.setBuffer(BHBuffer);

	// activate the window
	window.setActive(true);

	//this initialises the paddle and ball
	Paddle paddle(windowWidth / 2, windowHeight - 20);
	
	Ball ball(windowWidth / 2, 1);

	int score = 0;
	int lives = 3;

	// run the main loop
	bool running = true;

	float counter = 0.0f;
	
	std::cout << "" << std::endl;
	std::cout << "Bounce the ball off the" << std::endl;
	std::cout << "top to get a point." << std::endl;
	std::cout << "If it falls off the" << std::endl;
	std::cout << "bottom you lose a life." << std::endl;
	std::cout << "Don't lose all your lives though," << std::endl;
	std::cout << "or it's game over." << std::endl;
	std::cout << "" << std::endl;
	std::cout << "----CONTROLS----" << std::endl;
	std::cout << "LMB change Y Axis" << std::endl;
	std::cout << "RMB change X Axis" << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Current lives are " << lives << std::endl;
	
	//this is the game loop
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
		
		//if the left mouse button is pressed it will filp the direction the ball travels on the Y axis
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//std::cout << "Y flipped" << std::endl;
			ball.flipYVelocity();
		}

		//if the left mouse button is pressed it will filp the direction the ball travels on the X axis
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			//std::cout << "X flipped" << std::endl;
			ball.flipXVelocity();
		}

		//this will move the paddle left and play a sound, if the paddle is in a particular place
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			if (paddle.getPosition().left > -4.6)
			{
				//std::cout << "Move Left" << std::endl;
				//std::cout << "Paddle Position - Left: " << paddle.getPosition().left << std::endl;
				paddle.moveLeft();
				PaddleMove.play();
			}
		}

		//this will move the paddle right and play a sound, if the paddle is in a particular place
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			if (paddle.getPosition().left < 4.6)
			{
				//std::cout << "Move Right" << std::endl;
				//std::cout << "Paddle Position - Right: " << paddle.getPosition().left << std::endl;
				paddle.moveRight();
				PaddleMove.play();
			}
		}

		//this will turn exitMode true, which will allow the user to exit the game when enter is pressed
		else if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			std::cout << "Quit Game? Press Enter to leave" << std::endl;
			if (!exitMode)
			{
				Bye.play();
				exitMode = true;
			}
		}

		//this will exit the game completely, if exitMode is true, if not enter will not do anything
		else if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			if (exitMode)
			{
				std::cout << "Exit" << std::endl;
				window.close();
				running = false;
			}
		}

		//updates the ball and paddle
		ball.update();
		paddle.update(); 
		
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, 800.0f / 600.0f, 1.0f, 200.0f);
		
		//this draws the paddle and the ball
		drawCube(paddle.getPosition().left, -3, -9);
		drawCube(ball.getPosition().left, ball.getPosition().top, -13);

		//if the ball hits either the left or right side of the screen it will bounce
		//off in the opposite direction and go into a random direction on the Y axis
		if (ball.getPosition().left > 6.3 || ball.getPosition().left < -6.3)
		{
			float random = rand() % 201 + (-100);
			ball.flipXVelocity();
			ball.setYVelocity((float)(random / 1000));
			BallHit.play();
		}

		//if the ball bounces off the top of the screen it will bounce off in the opposite direction
		//you will also get a point
		if (ball.getPosition().top > 4.5)
		{
			score++;
			std::cout << "Your score is " << score << std::endl;
			ball.flipYVelocity();
			BallHit.play();
		}

		//this will reset the game if the ball goes off screen, when the ball respaws the direction of travel will be reversed
		//you will also lose a life
		if (ball.getPosition().top < -5)
		{
			
			lives--;
			std::cout << "Current lives are " << lives << std::endl;
			ball.reset();
			ball.flipYVelocity();
		}

		//if lives go down to 0, the game closes
		if (lives == 0)
		{
			running = false;
		}
		
		drawBackground(0, 0, -20);

		counter += 0.1f;
		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...
	return 0;
}