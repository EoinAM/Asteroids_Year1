#include "Bullet.h"
#include "Game.h"

/// <summary>
/// overloaded constructor
/// </summary>
/// <param name="texture">sprite sheet</param>
Bullet::Bullet(sf::Texture &texture)
{
	//set up the body
	body.setSize( sizeVector );
	body.setTexture(&texture );
	body.setTextureRect(sf::IntRect(237, 0, static_cast<int>(128), static_cast<int>(128)));//set the position of the image on the sprite sheet and the size of its rectangle
	
	//set up the bullet sound 
	if (!bulletBuffer.loadFromFile("ASSETS\\Sounds\\GunShot.wav"))
	{
		std::cout << "Gun sound not loaded" << std::endl;
	}
	bulletShotSound.setBuffer(bulletBuffer);
	bulletShotSound.setVolume(10);
}

Bullet::~Bullet()
{
}

/// <summary>
/// update the bullet position variables
/// </summary>
void Bullet::move()
{
	//if the bullet is alive
	if (isActive)
	{
		//update the positions
		position += bearing;
		center	 += bearing;
		body.setPosition(position);//set the bullet position

		timer++;
		//if the timer is greater than 250 set it to be false
		if (timer >= 250)
		{
			isActive = false;
			timer = 0;
		}

		//check screen wrapping
		if (position.Y() > 600)
		{
			position = { position.X(), (float)(0 - sizeVector.Y()), 0 };
			center = { position.X() + (sizeVector.X() * .5), (float)(0 - sizeVector.Y()) + (sizeVector.Y() * .5), 0 };
		}
		else if (position.Y() + sizeVector.Y() < 0 )
		{
			position = { position.X(), (float)(600), 0 };
			center = { position.X() + (sizeVector.X() * .5), (float)(600) + (sizeVector.Y() * .5), 0 };
		}
		else if (position.X() > 800)
		{
			position = { 0 - sizeVector.X(), position.Y(), 0 };
			center = { 0 - sizeVector.X() + (sizeVector.X() * .5), position.Y() + (sizeVector.Y() * .5), 0 };
		}
		else if (position.X() + sizeVector.X() < 0)
		{
			position = { 800, position.Y(), 0 };
			center = { 800 + (sizeVector.X() * .5), position.Y() + (sizeVector.Y() * .5), 0 };
		}
	}
	
}
