#include "Gems.h"
#include "Game.h"

/// <summary>
/// overloaded constructor
/// </summary>
/// <param name="texture"></param>
Gems::Gems(sf::Texture &texture)
{
	//set up the gem body
	body.setRadius( radius );
	body.setOrigin(radius, radius);
	body.setTexture(&texture);
	body.setTextureRect(sf::IntRect(125, 0, static_cast<int>(112), static_cast<int>(117)));//set the position of the image on the sprite sheet and the size of its rectangle
	body.setPosition(position);//set the body position
}

/// <summary>
/// default destructor
/// </summary>
Gems::~Gems()
{
}

/// <summary>
/// draw the gem object
/// </summary>
void Gems::render()
{
	//if the gem is alive then draw it
	if (isActive)
	{
		Game::m_window.draw(body);
	}
}

/// <summary>
/// //reset the gem
/// </summary>
void Gems::reset()
{
	isActive = false;
}
