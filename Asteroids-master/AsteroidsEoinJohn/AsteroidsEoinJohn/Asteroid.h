#ifndef ASTEROID
#define ASTEROID
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "MyVector3D.h"

//enum class for the size of the asteroid
enum AsteroidSize
{
	big,
	medium,
	small
};

class Asteroid
{
public:
	Asteroid(sf::Texture & texture);//overloaded constructor
	~Asteroid();//default destructor
	void update();//update asteroid variables
	void render();//draw the ateroid
	void reset(int number, MyVector3D passedPosition);//reset the asteroid at the start of a new level or when splitting asteroids

private:
	void move();//update the asteroids position
	void rotate(float angle);//rotate the asteroid

public:
	sf::CircleShape body;//body of the asteroid
	MyVector3D velocity{ 0,0,0 };//added to the position of the asteroid each frame to make it move
	MyVector3D position;//position of the asteroid
	MyVector3D bearing{ 0,-1,0 };//direction of the asteroid, used to calculate the velocity
	bool isAlive = false;//wether the asteroid is alive or not

	//used to decide what size the radius of an asteroid will be
	AsteroidSize currentSize;
	double radius{ 60 };

	//variables to do with the rotation of the asteroid
	double bearingAngle{ 0 };
	int direction{ 0 }, counter{ 0 };
	float rotationAngle{};

	//variables determining wether an asteroid will contain a gem
	bool isGemAvailable{ false };
	int gemPercentageChance{ 0 };

	//asteroid sounds
	sf::SoundBuffer asteroidBuffer;
	sf::Sound asteroidBreak;

private:
};


#endif