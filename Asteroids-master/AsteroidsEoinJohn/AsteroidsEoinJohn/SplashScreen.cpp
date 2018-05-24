#include "SplashScreen.h"
#include "Game.h"

/// <summary>
/// overloaded constructor
/// </summary>
/// <param name="font">font from main</param>
/// <param name="texture">spritesheet</param>
splash::splash(sf::Font & font, sf::Texture & texture)
{
	initialiseText(font);//set up text objects

	//set up the background sprite
	m_splashSprite.setTexture(texture);
	m_splashSprite.setTextureRect(sf::IntRect(703, 484, static_cast<int>(800), static_cast<int>(600)));//set the position of the image on the sprite sheet and the size of its rectangle
	m_splashSprite.setPosition(0, 0);//set the position for the sprite to draw from

	if (!gameBuffer.loadFromFile("ASSETS\\Sounds\\menuLoop.wav"))
	{
		std::cout << "failed to load background music" << std::endl;
	}
	backgroundMusic.setBuffer(gameBuffer);
	backgroundMusic.setLoop(true);
	backgroundMusic.setVolume(10);
	
	//backgroundMusic.play();
}

/// <summary>
/// default deconstructor
/// </summary>
splash::~splash()
{
}

/// <summary>
/// Process events polls while window is open
/// </summary>
/// <param name="">event from Game</param>
void splash::processEvents(sf::Event event)
{
	//if any key is pressed proceed onto the next screen
	if (event.type == sf::Event::KeyPressed)
	{
		m_proceed = true;
	}
}

/// <summary>
/// Update screen
/// </summary>
/// <param name="time">keeps track of text flash</param>
void splash::update(sf::Time time)
{
	//if proceed ids true move ontot he main menu screen
	if (m_proceed)
	{
		Game::m_currentGameMode = GameStatus::MainMenu;
	}
	else//otherwise flash the text a lighter and darkjer colour
	{
		m_cumulativeTime += time;
		if (m_cumulativeTime.asSeconds() > 0.5 && m_splashMessage.getFillColor() == TEXTCOLOUR1)
		{
			m_cumulativeTime = sf::Time::Zero;
			m_splashMessage.setFillColor(TEXTCOLOUR2);
		}
		else if(m_cumulativeTime.asSeconds() > 0.5 && m_splashMessage.getFillColor() == TEXTCOLOUR2)
		{
			m_cumulativeTime = sf::Time::Zero;
			m_splashMessage.setFillColor(TEXTCOLOUR1);
		}
	}
}

/// <summary>
/// Draw objects on screen
/// </summary>
void splash::render()
{
	//draw the prite and the text
	Game::m_window.draw(m_splashSprite);
	Game::m_window.draw(m_splashMessage);
}

/// <summary>
/// setup Onscreen Text
/// </summary>
/// <param name="font">font from main</param>
void splash::initialiseText(sf::Font & font)
{
	//set up text object
	m_splashMessage.setString("Press Any Key To Continue");
	m_splashMessage.setFont(font);
	m_splashMessage.setFillColor(TEXTCOLOUR1);
	m_splashMessage.setCharacterSize(25);
	m_splashMessage.setPosition((800 - m_splashMessage.getLocalBounds().width) / 2, ((600 - m_splashMessage.getLocalBounds().height) / 2) + 150);
}
