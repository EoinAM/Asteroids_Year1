#include "License.h"
#include "Game.h"

/// <summary>
/// overloaded Constructor
/// </summary>
/// <param name="font">font from main</param>
/// <param name="texture">spritesheet</param>
license::license(sf::Font & font, sf::Texture & texture)
{
	//set up the license screen message
	m_licenseMessage.setString("Crafted Lovingly By Eoin & John");
	m_licenseMessage.setFont(font);
	m_licenseMessage.setCharacterSize(25);
	m_licenseMessage.setFillColor(TEXTCOLOUR);
	m_licenseMessage.setPosition((800 - m_licenseMessage.getLocalBounds().width) / 2, (600 - m_licenseMessage.getLocalBounds().height) / 2 + 150);//centre the text

	m_JellySprite.setTexture(texture);
	m_JellySprite.setTextureRect(sf::IntRect(0, 484, static_cast<int>(703), static_cast<int>(500)));//set the position of the image on the sprite sheet and the size of its rectangle
	m_JellySprite.setScale(.7,.7);//scall the image accordingly
	m_JellySprite.setPosition(150,50);//centre the image

	m_licenseSprite.setTexture(texture);
	m_licenseSprite.setTextureRect(sf::IntRect(0, 1684, static_cast<int>(800), static_cast<int>(600)));//set the position of the image on the sprite sheet and the size of its rectangle
	m_licenseSprite.setPosition(0, 0);//draw from the origin
}

/// <summary>
/// default deconstructor
/// </summary>
license::~license()
{
}

/// <summary>
/// Update for splash screen
/// </summary>
/// <param name="time">time for lenght of license screen</param>
void license::update(sf::Time time)
{
	m_cumulativeTime += time;//add the time since the last frame to the amount of time passed
	//if more than three seconds has passed move onto the next screen
	if (m_cumulativeTime.asSeconds() > 3)
	{
		Game::m_currentGameMode = GameStatus::Splash;//set teh game mode to be splash screen
	}
}

/// <summary>
/// Draw objects to window
/// </summary>
void license::render()
{
	//draw the license screen objects
	Game::m_window.draw(m_licenseSprite);
	Game::m_window.draw(m_JellySprite);
	Game::m_window.draw(m_licenseMessage);
}
