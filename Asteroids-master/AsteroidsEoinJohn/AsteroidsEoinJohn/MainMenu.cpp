#include "MainMenu.h"
#include "Game.h"

/// <summary>
/// Default Constructor
/// </summary>
/// <param name="font">font from main</param>
/// <param name="texture">spritesheet from main</param>
Main::Main(sf::Font & font, sf::Texture & texture)
{
	initialiseButtons(font, texture);//call the initialise buttons function
}

/// <summary>
/// Default deconstructor
/// </summary>
Main::~Main()
{
}

/// <summary>
/// Main menu update
/// </summary>
void Main::update()
{
	//if the mouse position is insidethe bounds of a button
	if (sf::Mouse::getPosition(Game::m_window).x >= buttons[0].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[0].getPosition().x + sizeVector.X())
	{
		//loop through all of the buttons
		for (int i = 0; i < 4; i++)
		{
			if (sf::Mouse::getPosition(Game::m_window).y >= buttons[i].getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= buttons[i].getPosition().y + sizeVector.Y())
			{
				//change the size vector of the button to make it bigger
				buttons[i].setSize(buttonChange);
				updateButtonPos(i);//update its position so its centred
			}
			else if (!(sf::Mouse::getPosition(Game::m_window).y >= buttons[0].getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= buttons[0].getPosition().y + buttonChange.Y()))
			{
				//change the size vector of the button to make it smaller
				buttons[i].setSize(sizeVector);
				updateButtonPos(i);//update its position so its centred
			}
		}
	}
	//if the mouse isnt inside of a button bound
	else if (!(sf::Mouse::getPosition(Game::m_window).x >= buttons[0].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[0].getPosition().x + buttonChange.X()))
	{
		for (int i = 0; i < 3; i++)
		{
			//change the size vector of the button to make it smaller
			buttons[i].setSize(sizeVector);
			updateButtonPos(i);//update its position so its centred
		}

	}
}

/// <summary>
/// process events polls while window is open
/// </summary>
/// <param name="event">event passed from game</param>
void Main::processEvents(sf::Event event)
{
	//if the mouse button has been released
	if (sf::Event::MouseButtonReleased == event.type)
	{
		//loop for all buttons
		for (int i = 0; i < 4; i++)
		{
			//if the mouse is inside if a button
			if (sf::Mouse::getPosition(Game::m_window).x >= buttons[i].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[i].getPosition().x + buttonChange.X())
			{
				if (sf::Mouse::getPosition(Game::m_window).y >= buttons[i].getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= buttons[i].getPosition().y + buttonChange.Y())
				{
					//depending on the button change the current game mode
					switch (i)
					{
					case 0:
						Game::m_currentGameMode = GameStatus::LevelSelect;
						break;
					case 1:
						Game::m_currentGameMode = GameStatus::Hangar;
						break;
					case 2:
						Game::m_currentGameMode = GameStatus::HelpMenu;
						Game::m_previousGameMode = GameStatus::MainMenu;
						break;
					case 3:
						//close the game window and stop the program
						Game::m_window.close();
						break;
					}
				}
				//reset teh buttons to be the normal size and centre them
				for (int i = 0; i < 4; i++)
				{
					buttons[i].setSize(sizeVector);
					updateButtonPos(i);
				}
			}
		}
	}
}

/// <summary>
/// Objects drawn to screen
/// </summary>
void Main::render()
{
	//draw the background
	Game::m_window.draw(m_menuSprite);
	//loop for th buttons
	for (int i = 0; i < MAIN_MENU_MAX_BUTTONS; i++)
	{
		Game::m_window.draw(buttons[i]);//draw the buttons
		Game::m_window.draw(buttonText[i]);//draw the button text
	}
	Game::m_window.draw(m_titleText);//draw the title text
}

/// <summary>
/// Setup Buttons
/// </summary>
/// <param name="font">font on screen</param>
/// <param name="texture">spritesheet from main</param>
void Main::initialiseButtons(sf::Font & font,sf::Texture & texture)
{
	//initialise texts
	buttonText[0].setString("Play Game");
	buttonText[1].setString("Hangar");
	buttonText[2].setString("Help");
	buttonText[3].setString("Exit");
	//loop for all buttons
	for (int i = 0; i < MAIN_MENU_MAX_BUTTONS; i++)
	{
		//set up the buttons
		buttons[i].setSize(sizeVector);
		buttons[i].setTexture(&texture);
		buttons[i].setTextureRect(sf::IntRect(1385, 0, static_cast<int>(320), static_cast<int>(75)));
		buttons[i].setPosition((800 - buttons[i].getLocalBounds().width) / 2, (i * 100) + 200);
		//set up the texts
		buttonText[i].setFillColor(sf::Color::White);
		buttonText[i].setCharacterSize(30);
		buttonText[i].setFont(font);
		buttonText[i].setPosition((800 - buttonText[i].getLocalBounds().width) / 2, (i * 100) + 210);
	}
	//set up the title text
	m_titleText.setString("Asteroids");
	m_titleText.setCharacterSize(100);
	m_titleText.setFillColor(sf::Color::White);
	m_titleText.setFont(font);
	m_titleText.setPosition((800 - m_titleText.getLocalBounds().width) / 2, 30);

	//set up the background sprite
	m_menuSprite.setTexture(texture);
	m_menuSprite.setColor(sf::Color::Blue);
	m_menuSprite.setPosition(0, 0);
	m_menuSprite.setTextureRect(sf::IntRect(800, 1084, static_cast<int>(800), static_cast<int>(600)));

}

/// <summary>
/// update the button position so it is centred when the size vector is changed
/// </summary>
/// <param name="i"></param>
void Main::updateButtonPos(int i)
{
	buttons[i].setPosition((800 - buttons[i].getLocalBounds().width) / 2, (i * 100) + 200);
}

