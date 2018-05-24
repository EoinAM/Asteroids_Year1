#include "Pause.h"
#include "Game.h"

/// <summary>
/// Overloaded Constructor
/// </summary>
/// <param name="font">font from main</param>
/// <param name="texture">spritesheet fromm main</param>
PauseMenu::PauseMenu(sf::Font & font, sf::Texture & texture)
{
	initialiseButtons(font, texture);//set up the buttons
}

/// <summary>
/// default deconstructor
/// </summary>
PauseMenu::~PauseMenu()
{
}

/// <summary>
/// process user input
/// </summary>
/// <param name="event">window polled event</param>
void PauseMenu::processEvents(sf::Event event)
{
	//if the mouse button is released
	if (sf::Event::MouseButtonReleased == event.type)
	{
		//loop through all the buttons
		for (int i = 0; i < 3; i++)
		{
			//if the mouse position is over a button
			if (sf::Mouse::getPosition(Game::m_window).x >= buttons[i].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[i].getPosition().x + buttonChange.X())
			{
				if (sf::Mouse::getPosition(Game::m_window).y >= buttons[i].getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= buttons[i].getPosition().y + buttonChange.Y())
				{
					//depending on which button
					switch (i)
					{
					case 0:
						Game::m_currentGameMode = GameStatus::Playing;//set the gamemode to playing
						break;
					case 1:
						Game::m_currentGameMode = GameStatus::HelpMenu;//set the gamemode to help
						Game::m_previousGameMode = GameStatus::Pause;//set the previous game mode to be pausee
						break;
					case 2:
						Game::m_currentGameMode = GameStatus::LevelSelect;//set the gamemode to main mneu
						break;
					}
				}
				//update the button positions
				for (int i = 0; i < 3; i++)
				{
					buttons[i].setSize(sizeVector);
					updateButtonPos(i);
				}
			}
		}
	}
}

/// <summary>
/// Game Update per 60 fps
/// </summary>
void PauseMenu::update()
{
	//if the mouse position is over a button
	if (sf::Mouse::getPosition(Game::m_window).x >= buttons[0].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[0].getPosition().x + sizeVector.X())
	{
		for (int i = 0; i < 3; i++)
		{
			if (sf::Mouse::getPosition(Game::m_window).y >= buttons[i].getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= buttons[i].getPosition().y + sizeVector.Y())
			{
				//update the button
				buttons[i].setSize(buttonChange);
				updateButtonPos(i);
			}
			else if (!(sf::Mouse::getPosition(Game::m_window).y >= buttons[0].getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= buttons[0].getPosition().y + buttonChange.Y()))
			{
				//update the button
				buttons[i].setSize(sizeVector);
				updateButtonPos(i);
			}
		}
	}
	else if (!(sf::Mouse::getPosition(Game::m_window).x >= buttons[0].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[0].getPosition().x + buttonChange.X()))
	{
		for (int i = 0; i < 3; i++)
		{
			//update the button
			buttons[i].setSize(sizeVector);
			updateButtonPos(i);
		}

	}
	
}

/// <summary>
/// Draw objects to screen
/// </summary>
void PauseMenu::render()
{
	//draw the buttons and text
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		Game::m_window.draw(buttons[i]);
		Game::m_window.draw(buttonText[i]);
	}
	Game::m_window.draw(m_titleText);
}

/// <summary>
/// Setup buttons on the screen
/// </summary>
/// <param name="font">font from main</param>
/// <param name="texture">spritesheet</param>
void PauseMenu::initialiseButtons(sf::Font & font, sf::Texture & texture)
{
	//set up the buttons and text
	buttonText[0].setString("Continue");
	buttonText[1].setString("Help Menu");
	buttonText[2].setString("Exit");
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		buttons[i].setTexture(&texture);
		buttons[i].setTextureRect(sf::IntRect(1385, 0, static_cast<int>(320), static_cast<int>(75)));
		buttons[i].setSize(sizeVector);
		updateButtonPos(i);

		buttonText[i].setFillColor(sf::Color::White);
		buttonText[i].setCharacterSize(30);
		buttonText[i].setFont(font);
		buttonText[i].setPosition((800 - buttonText[i].getLocalBounds().width) / 2.f, (float)((i * 125) + 215));
	}
	m_titleText.setString("Pause");
	m_titleText.setFillColor(ASTEROIDTEXTCOLOUR);
	m_titleText.setCharacterSize(60);
	m_titleText.setFont(font);
	m_titleText.setPosition((800 - m_titleText.getLocalBounds().width) / 2.f,65);
}

/// <summary>
/// Update position of buttons when hovered over
/// </summary>
/// <param name="i">Max Buttons</param>
void PauseMenu::updateButtonPos(int i)
{
	//cetre the buttons on screen
	buttons[i].setPosition((800 - buttons[i].getLocalBounds().width) / 2.f, (float)((i * 125) + 200));
}
