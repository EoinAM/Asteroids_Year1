#ifndef BULLET
#define BULLET

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include "MyVector3D.h"

class Bullet
{
public:
	Bullet(sf::Texture &texture);//overloaded constructor
	~Bullet();//default destructor

	void move();//update bullet position variables
	
public:
	sf::RectangleShape body;//body of the bullet
	bool isActive{ false};//wether it is alive or not
	MyVector3D position{ 0,0,0 };//bullet position
	MyVector3D bearing{ 0,0,0 };//bullet direction
	MyVector3D sizeVector{ 20, 35, 0};//size of the bullet

	MyVector3D center{ position.X() + (sizeVector.X() * .5), position.Y() + (sizeVector.Y() * .5), 0 };//centre of the bullet
	int timer{ 0 };//timer

	//sound variables
	sf::SoundBuffer bulletBuffer;
	sf::Sound bulletShotSound;

};

#endif // !BULLET
