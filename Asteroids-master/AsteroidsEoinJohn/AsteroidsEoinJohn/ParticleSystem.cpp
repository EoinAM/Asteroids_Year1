#include "ParticleSystem.h";
#include "Game.h"

/// <summary>
/// Default deconstructor
/// </summary>
ParticleSystem::ParticleSystem()
{
}

/// <summary>
/// default deconstructor
/// </summary>
ParticleSystem::~ParticleSystem()
{
}

/// <summary>
/// Particle default constructor
/// </summary>
Particle::Particle()
{
}

/// <summary>
/// particle constructor with  arguments
/// </summary>
/// <param name="position">position particle spawns</param>
/// <param name="velocity">velocity of particles</param>
Particle::Particle(MyVector3D aposition, MyVector3D avelocity)
{
	m_body.setSize(size);//set the size of body
	m_body.setPosition(aposition);//set the position of the body
	m_body.setFillColor(sf::Color::Black);//set the colour of the particle

	velocity = avelocity;//set the velocity to be the velocity that is passed
	timer = rand() % 80;//make the particle last for a random length from 0 to 80
}

/// <summary>
/// Default deconstructor
/// </summary>
Particle::~Particle()
{
}

/// <summary>
/// Spawn in the particles
/// </summary>
/// <param name="aposition">position particles spawn</param>
void ParticleSystem::initialise(MyVector3D aposition)
{
	//set the position of the particle system to be the position passed to the function
	position = aposition;
	//loop for max particles
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		//initialise each particle
		particles[i] = Particle(position, MyVector3D(rand() / double(RAND_MAX) * 4 - 2, rand() / double(RAND_MAX) * 4 - 2, 0));
	}
}

/// <summary>
/// Update the particles positions
/// </summary>
void ParticleSystem::update()
{
	//for each particle
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		//if the timer is greater than 0
		if (particles[i].timer > 0)
		{
			//move the particle
			particles[i].m_body.move(particles[i].velocity);
			particles[i].timer--;//decrease its timer
		}
	}
}

/// <summary>
/// Draw the particles on the window
/// </summary>
void ParticleSystem::render()
{
	//for all of the particles
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		//if the timer is greater than 0
		if (particles[i].timer > 0)
		{
			//draw the particle body
			Game::m_window.draw(particles[i].m_body);
		}
	}
}