#include "LevelSelect.h"
#include "Game.h"
#include <iostream>

/// <summary>
/// Default Constructor
/// </summary>
/// <param name="font">font passed from main</param>
/// <param name="texture">spritesheet from main</param>
LevelSelectScreen::LevelSelectScreen(sf::Font & font, sf::Texture & texture)
{
	initialiseButtons(font, texture);//call the function to set up the text and buttons
}

/// <summary>
/// Default deconstructor
/// </summary>
LevelSelectScreen::~LevelSelectScreen()
{
}

/// <summary>
/// SetUp buttons and text
/// </summary>
/// <param name="font">Font for text</param>
/// <param name="texture">spritesheet for buttons</param>
void LevelSelectScreen::initialiseButtons(sf::Font & font, sf::Texture &texture)
{
	//set the text strings
	buttonText[0].setString("Level 1");
	buttonText[1].setString("Level 2");
	buttonText[2].setString("Level 3");
	buttonText[3].setString("Level 4");
	buttonText[4].setString("Level 5");
	buttonText[5].setString("Level 6");
	buttonText[6].setString("Level 7");
	buttonText[7].setString("Level 8");
	buttonText[8].setString("Level 9");

	//set up the background sprite
	m_levelSelectSprite.setTexture(texture);
	m_levelSelectSprite.setPosition(0, 0);//draw from the origin
	m_levelSelectSprite.setTextureRect(sf::IntRect(800, 1084, static_cast<int>(800), static_cast<int>(600)));//set the position of the image on the sprite sheet and the size of its rectangle

	//loop through all of the buttons
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		buttons[i].setTexture(&texture);//set the texture
		//set the position of the image on the sprite sheet and the size of its rectangle
		buttons[i].setTextureRect(sf::IntRect(365, 0, static_cast<int>(200), static_cast<int>(150))); //not playable level texture
		buttons[i].setSize(sizeVector);//set the size
		buttonText[i].setFillColor(sf::Color::White);
		
		//centre the button
		updateButtonPos(i);
		setTextPos(i);//set the text positions in the function

		//initialise the rest of the text variables
		buttonText[i].setFillColor(ASTEROIDTEXTCOLOUR);
		buttonText[i].setCharacterSize(30);
		buttonText[i].setFont(font);
	}
}


/// <summary>
/// Process Events, polls while window is open
/// </summary>
/// <param name="event">event from game</param>
/// <param name="asteroid">Asteroid Object</param>
/// <param name="livingAsteroids"> how many asteroids are alive</param>
/// <param name="levelActive"> how many of the alive are active</param>
/// <param name="player"> Player object</param>
void LevelSelectScreen::processEvents(sf::Event event, Asteroid asteroid[], int MAX_ASTEROIDS, bool levelActive[], Player &player, bool &gameOver, Gems gemArray[])

{
	//if the escape button is pressed return to the main menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Game::m_currentGameMode = GameStatus::MainMenu;
	}
	//if the mouse button is released
	if (sf::Event::MouseButtonReleased == event.type)
	{
		//loop for all the buttons
		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			//if the mouse position is inside of the buttons
			if (sf::Mouse::getPosition(Game::m_window).x >= buttons[i].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[i].getPosition().x + buttonChange.X())
			{
				if (sf::Mouse::getPosition(Game::m_window).y >= buttons[i].getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= buttons[i].getPosition().y + buttonChange.Y())
				{
					//if the level is currently playable
					if (Game::levelPlayable[i])
					{

						Game::m_currentGameMode = GameStatus::Playing;
						player.reset();//reset the player
						Game::startingAsteroids = asteroidNumber[i];//set how many asteroids startt he game
						//loop for all asteroids
						for (int i = 0; i < MAX_ASTEROIDS; i++)
						{
							//only reset the starting asteroids
							if (i < Game::startingAsteroids)
							{
								//set them to be at a random position and a random size
								asteroid[i].reset(rand() % 3, MyVector3D{ (double)(rand() % 800),(double)(rand() % 600), 0 });
							}
							else
							{
								//otherwise set the asteroid o =to not be alive
								asteroid[i].isAlive = false;
							}
							gemArray[i].reset();//reset all of the gems
							gameOver = false;//set gameover to be false
						}
						for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < MAX_PARTICLES; j++)
							{
								Game::particleEffects[i].particles[j].timer = 0;
							}
						}
						Game::activeLevel = i + 1;//set the active game to be i + 1 so that if the game is cleared the next level can be set to be active
					}
				}
			}
			//loop for all buttons
			for (int i = 0; i < 9; i++)
			{
				//recentre the button
				buttons[i].setSize(sizeVector);
				updateButtonPos(i);
			}
		}
	}
}

/// <summary>
/// Draw Objects in the game window
/// </summary>
void LevelSelectScreen::update(bool levelActive[])
{
	//loop for all buttons
	for (int i = 0; i < 9; i++)
	{
		//if the level is playable
		if (Game::levelPlayable[i])
		{
			//set it to have the blue texture
			buttons[i].setTextureRect(sf::IntRect(565, 0, static_cast<int>(200), static_cast<int>(150)));//set the position of the image on the sprite sheet and the size of its rectangle
			buttonText[i].setFillColor(sf::Color::White);
		}
		else
		{
			//otherwise set it to have the red texture
			buttons[i].setTextureRect(sf::IntRect(365, 0, static_cast<int>(200), static_cast<int>(150)));//set the position of the image on the sprite sheet and the size of its rectangle
			buttonText[i].setFillColor(ASTEROIDTEXTCOLOUR);
		}
		//if the mouse position is inside of the buttons
		if (sf::Mouse::getPosition(Game::m_window).x >= buttons[i].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[i].getPosition().x + sizeVector.X())
		{
			if (sf::Mouse::getPosition(Game::m_window).y >= buttons[i].getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= buttons[i].getPosition().y + sizeVector.Y())
			{
				//make the button bigger and recentre it
				buttons[i].setSize(buttonChange);
				updateButtonPos(i);
			}
			else
			{
				//otherwise make the button smaller and recentre it
				buttons[i].setSize(sizeVector);
				updateButtonPos(i);
			}
		}
		//if ht e mouse position isnt inside of the buttons
		else if (!(sf::Mouse::getPosition(Game::m_window).x >= buttons[i].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[i].getPosition().x + buttonChange.X()))
		{
			//make the buttons smaller and  recentre them
			buttons[i].setSize(sizeVector);
			updateButtonPos(i);
		}
	}
}

/// <summary>
/// Update positions of the button
/// </summary>
/// <param name="i">Max Buttons</param>
void LevelSelectScreen::render()
{
	//draw the background sprite
	Game::m_window.draw(m_levelSelectSprite);
	//loop for all buttons
	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		//draw the buttons and text objects
		Game::m_window.draw(buttons[i]);
		Game::m_window.draw(buttonText[i]);
	}
}

/// <summary>
/// set up the position of the text
/// </summary>
/// <param name="i">Max Buttons</param>
void LevelSelectScreen::updateButtonPos(int i)
{
	int scalar = 0;//scalar used to place the buttons in the correct position
	if (i == 0 || i == 3 || i == 6)//if button 0,3,6 to be updated
	{
		if (i == 3)
		{
			scalar = 1;
		}
		else if (i == 6)
		{
			scalar = 2;
		}
		//set the button position
		buttons[i].setPosition((((800 / 3.0f) - buttons[i].getLocalBounds().width) / 2), 35 + (190 * scalar));
	}
	else if (i == 1 || i == 4 || i == 7)//if button 1,4,7 to be updated
	{
		if (i == 4)
		{
			scalar = 1;
		}
		else if (i == 7)
		{
			scalar = 2;
		}
		//set the button position
		buttons[i].setPosition((((800 / 3.0f) - buttons[i].getLocalBounds().width) / 2) + 265, 35 + (190 * scalar));
	}
	else if (i == 2 || i == 5 || i == 8)//if button 2,5,8 to be updated
	{
		if (i == 5)
		{
			scalar = 1;
		}
		else if (i == 8)
		{
			scalar = 2;
		}
		//set the button position
		buttons[i].setPosition((((800 / 3.0f) - buttons[i].getLocalBounds().width) / 2) + 530, 35 + (190 * scalar));
	}
}

/// <summary>
/// set up the text positions depending on which text is being set
/// </summary>
/// <param name="i">which text element is being set</param>
void LevelSelectScreen::setTextPos(int i)
{
	int scalar = 0;//scalar used to place the text in the correct position

	//set the scalar appropriately
	if (i == 3 || i == 4 || i == 5)
	{
		scalar = 1;
	}
	else if (i == 6 || i == 7 || i == 8)
	{
		scalar = 2;
	}

	//set the text positions
	if (i == 0 || i == 3 || i == 6) //if text 0,3,6 to be updated
	{
		buttonText[i].setPosition((((800 / 3.0f) - buttons[i].getLocalBounds().width) / 2) + 50, 80 + (190 * scalar));
	}
	else if (i == 1 || i == 4 || i == 7)//if text 1,4,7 to be updated
	{
		buttonText[i].setPosition((((800 / 3.0f) - buttons[i].getLocalBounds().width) / 2) + 315, 80 + (190 * scalar));
	}
	else if (i == 2 || i == 5 || i == 8)//if text 2,5,8 to be updated
	{
		buttonText[i].setPosition((((800 / 3.0f) - buttons[i].getLocalBounds().width) / 2) + 580, 80 + (190 * scalar));
	}
}
