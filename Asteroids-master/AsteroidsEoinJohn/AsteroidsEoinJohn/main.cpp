#include <iostream>
#include "Game.h"
//include libraries for the rng
#include <ctime>
#include <cstdlib>

/// <summary>
/// @Authors Eoin Abbey-Maher & John Foley
/// @date 21-02-17
/// bug declaration:
/// bullets dont shoot from the centre of the sprite as the sprite is slightly oddly shaped, we have combatted this as best we could think to
/// sometimes the bullet collision doesnt work with the small asteroids and the bullet moves through them
/// sometimes the bullets disappear early, or sometimes the bullet sound plays and the bullet doesnt appear or interact with the world
/// </summary>
void main()
{
	srand(time(nullptr));//sets the seed for the project

	//game font
	sf::Font m_gameFont;
	//game sprite sheet
	sf::Texture spriteSheet;

	//load the sprite sheet
	if (!spriteSheet.loadFromFile("ASSETS\\Sprites\\spriteSheet.png"))
	{
		std::cout << "Sprite Sheet Not Loaded" << std::endl;
	}
	//load the font
	if (!m_gameFont.loadFromFile("ASSETS\\FONTS\\MILLENNIA.ttf"))
	{
		std::cout << "Font Not Loaded" << std::endl;
	}

	Game game( m_gameFont, spriteSheet );//create a game object using the overloaded constructor
	game.run();//call the run function in the game class
}