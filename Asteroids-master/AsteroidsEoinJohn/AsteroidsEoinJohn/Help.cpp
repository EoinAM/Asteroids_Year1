#include "Help.h"
#include "Game.h"

/// <summary>
/// Help screen Constructor 
/// </summary>
/// <param name="font">font passed from Main Menu</param>
/// <param name="texture">spritesheet </param>
HelpScreen::HelpScreen(sf::Font & font, sf::Texture & texture)
{
	initialiseText(font, texture);//set up all of the text objects
}

/// <summary>
/// Default Decontructor
/// </summary>
HelpScreen::~HelpScreen()
{
}

/// <summary>
/// Process events, polls when window is open
/// </summary>
/// <param name="event">event passed from game.cpp</param>
void HelpScreen::processEvents(sf::Event event)
{
	//if the escape key is pressed return to whichever screen it came from
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Game::m_currentGameMode = Game::m_previousGameMode;
	}
	
	//if the mouse button is released
	if (sf::Event::MouseButtonReleased == event.type)
	{
		//if the mouse position is inside of the button
		if (sf::Mouse::getPosition(Game::m_window).x >= m_button.getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= m_button.getPosition().x + buttonScale.X())
		{
			if (sf::Mouse::getPosition(Game::m_window).y >= m_button.getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= m_button.getPosition().y + buttonScale.Y())
			{
				//return to the previous game screen
				Game::m_currentGameMode = Game::m_previousGameMode;
			}
		}
		//reset the buttons
		m_button.setSize(sizeVector);
		updateButtonPos();//recentre the button
	}
}

/// <summary>
/// Controls button size increase when hovered over
/// </summary>
void HelpScreen::update()
{
	//if the mouse position is inside of a button
	if (sf::Mouse::getPosition(Game::m_window).x >= m_button.getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= m_button.getPosition().x + buttonScale.X())
	{
		if (sf::Mouse::getPosition(Game::m_window).y >= m_button.getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= m_button.getPosition().y + buttonScale.Y())
		{
			//make the button bigger
			m_button.setSize(buttonScale);
			updateButtonPos();//recentre the button
		}
		else
		{
			//make the button smaller
			m_button.setSize(sizeVector);
			updateButtonPos();//recentre the button
		}
	}
	else if (!(sf::Mouse::getPosition(Game::m_window).x >= m_button.getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= m_button.getPosition().x + buttonScale.X()))
	{
		//make the button smaller
		m_button.setSize(sizeVector);
		updateButtonPos();//recentre the button
	}
	updateButtonPos();//recentre the button
}

/// <summary>
/// Draw the objects into the game window
/// </summary>
void HelpScreen::render()
{
	//draw all of the help menu objects
	Game::m_window.draw(m_background);
	Game::m_window.draw(m_button);
	Game::m_window.draw(m_buttonText);//draw the text
}

/// <summary>
/// set up the return button
/// </summary>
void HelpScreen::updateButtonPos()
{
	m_button.setPosition((800 - m_button.getLocalBounds().width) / 2, 475);//recentre the button
}

/// <summary>
/// Set up Text and buttons on help menu
/// </summary>
/// <param name="font">passed from main</param>
/// <param name="texture">spritesheet from main</param>
void HelpScreen::initialiseText(sf::Font & font, sf::Texture &texture)
{
	//initialise and set the string of the help menu text
	m_helpText.setString("Insert Text String With\nControls Of Game Here");
	m_helpText.setFont(font);
	m_helpText.setFillColor(sf::Color::White);
	m_helpText.setCharacterSize(20);
	m_helpText.setPosition((800 - m_helpText.getLocalBounds().width) / 2, ((600 - m_helpText.getLocalBounds().height) / 2));
	
	//if the background texture isnt loaded output a message
	if (!m_backgroundTexture.loadFromFile("ASSETS\\Sprites\\HelpScreen.png"))
	{
		std::cout << "help loaded" << std::endl;
	}
	m_background.setTexture(m_backgroundTexture);//set up the background texture
	m_background.setPosition(0, 0);//draw form the origin
	
	//set up and initialise the string of the help menu button
	m_buttonText.setString("Return");
	m_buttonText.setFont(font);
	m_buttonText.setFillColor(sf::Color::White);
	m_buttonText.setCharacterSize(20);
	m_buttonText.setPosition((800 - m_buttonText.getLocalBounds().width) / 2, 500);//centre the utton

	//set up the button
	m_button.setSize(sizeVector);
	m_button.setTexture(&texture);
	m_button.setTextureRect(sf::IntRect(1385, 0, static_cast<int>(320), static_cast<int>(75)));//set the position of the image on the sprite sheet and the size of its rectangle
	m_button.setPosition((800 - m_button.getLocalBounds().width) / 2, 475);//centre the button
}
