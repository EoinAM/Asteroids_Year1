
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include "Asteroid.h"
#include "Game.h"


/// <summary>
/// overloaded constructor
/// </summary>
/// <param name="texture">sprite sheet</param>
Asteroid::Asteroid(sf::Texture & texture)
{
	body.setTexture(&texture);//set the texture of the body
}

/// <summary>
/// default destructor
/// </summary>
Asteroid::~Asteroid()
{
}

/// <summary>
/// update any variables to do with the asteroid
/// </summary>
void Asteroid::update()
{
	move();//call the move function

	//if direction is 0
	if (direction == 0)
	{
		//rotate clockwise
		rotate(rotationAngle);
	}
	else
	{
		//rotate counter clockwise
		rotate(-rotationAngle);
	}
}

/// <summary>
/// used to reset asteroids both at the start of a new level and when splitting asteroids
/// </summary>
/// <param name="number">the size of the asteroid</param>
/// <param name="tempPosition">the position of the asteroid</param>
void Asteroid::reset(int number, MyVector3D passedPosition)
{
	//depending on the number set the size of the asteroid
	switch (number)
	{
	case 0:
		currentSize = AsteroidSize::big;
		break;
	case 1:
		currentSize = AsteroidSize::medium;
		break;
	case 2:
		currentSize = AsteroidSize::small;
		break;
	}


	radius = 60;//reset the radius
	//depending on the current size of the ateroid set its raius and sprite
	switch (currentSize)
	{
	case big:
		body.setRadius((float)radius);
		body.setOrigin(radius, radius);
		body.setTextureRect(sf::IntRect(65, 0, static_cast<int>(60), static_cast<int>(60)));//set the position of the image on the sprite sheet and the size of its rectangle
		break;
	case medium:
		radius = radius * .75;
		body.setRadius((float)radius);
		body.setOrigin(radius, radius);
		body.setTextureRect(sf::IntRect(25, 0, static_cast<int>(40), static_cast<int>(40)));//set the position of the image on the sprite sheet and the size of its rectangle
		break;
	case small:
		radius = radius * .5;
		body.setRadius((float)radius);
		body.setOrigin(radius, radius);
		body.setTextureRect(sf::IntRect(0, 0, static_cast<int>(25), static_cast<int>(25)));//set the position of the image on the sprite sheet and the size of its rectangle
		break;
	default:
		break;
	}

	
	position = passedPosition;//set the position to be what is passed to the function
	body.setPosition(position);//set the position of the body

	bearingAngle = (rand() % 6) + 0.1;//randomise what direction the asteroid will shoot off in
	bearing = { 0,-1,0 };//reset the bearing
	//turn the bearing so it faces the right direction
	bearing.m_x = bearing.X() * cos((float)bearingAngle) - bearing.Y() * sin((float)bearingAngle);
	bearing.m_y = bearing.X() * sin((float)bearingAngle) + bearing.Y() * cos((float)bearingAngle);
	//set the velocity to be equal to this bearing
	velocity = bearing;
	velocity = velocity * (float)((rand() % 4) + 2);//randomlymake the velocity slightly faster
	direction = rand() % 2;//direction decides wether the asteroid rotates clockwise or anticlockwise
	rotationAngle = (rand() % 2) + 1;//the angle at which the asteroid rotates 
	counter = 0;//reset counter
	body.setRotation(0);//reset the body rotation
	gemPercentageChance = (int)(rand() % 100);//generate a number to see if an asteroid will contain a gem

	//if the number generated is less than 20 then it will contain a gem otherwise it wont
	if (gemPercentageChance <= 30)
	{
		isGemAvailable = true;
	}
	else
	{
		isGemAvailable = false;
	}
	//set the asteroid to be alive
	isAlive = true;

	//load the asteroid breaking sound
	if (!asteroidBuffer.loadFromFile("ASSETS\\Sounds\\AsteroidBreak.wav"))
	{
		std::cout << "asteroidbreak not loaded" << std::endl;
	}
	asteroidBreak.setBuffer(asteroidBuffer);//set the buffer
	asteroidBreak.setVolume(20);//set the volume
}

/// <summary>
/// update the asteroids position
/// </summary>
void Asteroid::move()
{
	if (isAlive)
	{
		position += velocity;
		//check screen wrapping
		//left
		if (position.X() < (0 - 2 * radius))
		{
			position = { 800, position.Y(),0 };
		}
		//right
		else if (position.X() > 800 + 2 * radius)
		{
			position = { (float)(0 - radius), position.Y(),0 };
		}
		//top
		else if (position.Y() < (0 - 2 * radius))
		{
			position = { position.X(), (float)600 + radius,0 };
		}
		//bottom
		else if (position.Y() > 600 + 2 * radius)
		{
			position = { position.X(), (float)(0 - radius),0 };
		}
		//set the position of the body
		body.setPosition(position);
	}
}

/// <summary>
/// roatate the asteroid
/// </summary>
/// <param name="angle"></param>
void Asteroid::rotate(float direction)
{
	//depending onw which way the asteroid is spinning add or subtract from the counter
	if (direction > 0)
	{
		counter++;
	}
	else
	{
		counter--;
	}

	//if the asteroid has rotate a full 360 degrees reset th counter and body rotation to be 0
	if (counter >= (360 / rotationAngle) || counter <= -(360 / rotationAngle))
	{
		counter = 0;
		body.setRotation(0);
	}
	else
	{
		body.rotate(direction);//rotate the body by the rotation angle
	}
}


void Asteroid::render()
{
	//if the asteroid is alive draw it
	if (isAlive)
	{
		Game::m_window.draw(body);
	}
}