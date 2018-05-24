#ifndef PARTICLESYSTEM
#define PARTICLESYSTEM

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "MyVector3D.h"
#include "Particle.h"

//Max amount of particles
const int MAX_PARTICLES{ 200 };
class ParticleSystem
{
public:
	ParticleSystem();//default constructor
	~ParticleSystem();//default destructor
	void initialise(MyVector3D aposition);//initialse the particle system and all particles inside of it
	void update();//update all of the particles in the system
	void render();//dra all of the particles in the system

public:
	//array of particle objects
	Particle particles[MAX_PARTICLES];
	//position of particle system
	MyVector3D position;

private:

};

#endif // !PARTICLESYSTEM
