#ifndef PARTICLE
#define PARTICLE

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include "MyVector3D.h"

class Particle
{
public:
	Particle();//default particle constructor
	Particle(MyVector3D position, MyVector3D velocity);//overloaded particle constructor
	~Particle();//default destructor

public:
	//timer for how long particle is alive
	int timer{ 0 };
	//rectangle for body
	sf::RectangleShape m_body;
	//particle size
	MyVector3D size{ 6,6,0 };
	//particle Velocity
	MyVector3D velocity{ 4,4,0 };
};


#endif // !PARTICLE

