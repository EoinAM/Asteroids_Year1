#include "HangarScreen.h"
#include "Game.h"

/// <summary>
/// constructor being passed a font and texture from Main
/// </summary>
HangarScreen::HangarScreen(sf::Font & font, sf::Texture & texture) : 
	//initialise the boolean arrays
	available{ { true },{ false },{ true },{ false },{ true },{ false },{ true },{ false }, {true} },
	buttonUsed{ { false },{ false },{ false },{ false },{ false },{ false },{ false },{ false } }
{
	initialiseButtons(font, texture);//initialise the buttons and text objects
}

/// <summary>
/// Default Deconstructor
/// </summary>
HangarScreen::~HangarScreen()
{
}

/// <summary>
/// Hangar screenupdate being passed the Player and will be passed into the Game update
/// </summary>
void HangarScreen::update(Player player)
{
	//updatwe the GEM score text
	m_scoreText.setString("G.E.M.S: " + std::to_string(player.score));
	m_scoreText.setPosition((800 - m_scoreText.getLocalBounds().width) / 2, 80);//centre the text

	//loop for each button
	for (int i = 0; i < 9; i++)
	{
		//depending on which button
		switch (i)
		{
		case 0:
		case 2:
		case 4:
		case 6:
			//if you dont have the gems or the button is used already
			if (player.score < buttonCost[i] || buttonUsed[i])
			{
				//set it to be false
				available[i] = false;
			}
			else
			{
				//otherwise set it to be true
				available[i] = true;
			}
			break;
		case 1:
		case 3:
		case 5:
		case 7:
			//if you dont have enough gems, or the button has been used before, or the prerequisite hasnt been used
			if (player.score < buttonCost[i] || buttonUsed[i] || !buttonUsed[i - 1])
			{
				//set the button to be false
				available[i] = false;
			}
			else
			{
				//otherwise set it to be true
				available[i] = true;
			}
			break;
		}

		//if the button is available
		if (available[i])
		{
			//set the texture to be the blue texture
			buttons[i].setTextureRect(sf::IntRect(1385, 0, static_cast<int>(320), static_cast<int>(75)));//set the position of the image on the sprite sheet and the size of its rectangle
			//change the text colour to stand out against the 
			if (i < 8)
			{
				//set the text colour to be blue
				costText[i].setFillColor(ASTEROIDTEXTCOLOUR);
			}
		}
		else
		{
			//otherwise set the texture to be the red one
			buttons[i].setTextureRect(sf::IntRect(1065, 0, static_cast<int>(320), static_cast<int>(75)));//set the position of the image on the sprite sheet and the size of its rectangle
			if (i < 8)
			{
				//set the text colour to be white
				costText[i].setFillColor(sf::Color::White);
			}
		}

		//if the mouse position is inside of a button
		if (sf::Mouse::getPosition(Game::m_window).x >= buttons[i].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[i].getPosition().x + sizeVector.X())
		{
			if (sf::Mouse::getPosition(Game::m_window).y >= buttons[i].getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= buttons[i].getPosition().y + sizeVector.Y())
			{
				//set the button to be bigger
				buttons[i].setSize(buttonChange);
				updateButtonPos(i);//update the button position
			}
			else
			{
				//otherwise set the button to be smaller
				buttons[i].setSize(sizeVector);
				updateButtonPos(i);//update the button position
			}
		}
		//othewise if the mouse position isnt inside of the buttons
		else if (!(sf::Mouse::getPosition(Game::m_window).x >= buttons[i].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[i].getPosition().x + buttonChange.X()))
		{
			//set the button to be smaller
			buttons[i].setSize(sizeVector);
			updateButtonPos(i);//update the button position
		}
	}
}

/// <summary>
/// Process events polled when window is open
/// </summary>
/// <param name="event">event passed from the Game.cpp</param>
/// <param name="player"> Player object</param>
void HangarScreen::processEvents(sf::Event event, Player &player)
{
	//if the escape key is pressed return to the main menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Game::m_currentGameMode = GameStatus::MainMenu;
	}

	//if the mouse button is released
	if (sf::Event::MouseButtonReleased == event.type)
	{
		//loop for all of the buttons
		for (int i = 0; i < 9; i++)
		{
			//if the mouse position is inside of the buttons
			if (sf::Mouse::getPosition(Game::m_window).x >= buttons[i].getPosition().x && sf::Mouse::getPosition(Game::m_window).x <= buttons[i].getPosition().x + buttonChange.X())
			{
				if (sf::Mouse::getPosition(Game::m_window).y >= buttons[i].getPosition().y && sf::Mouse::getPosition(Game::m_window).y <= buttons[i].getPosition().y + buttonChange.Y())
				{
					//if the button is available
					if (available[i])
					{
						//depending on the button
						switch (i)
						{
						case 0:
						case 2:
						case 4:
						case 6:
							available[i] = false;//set it to be false
							available[i + 1] = true;//set the next buttons availability to be true
							buttonUsed[i] = true;//set the button used to be true
							player.score -= buttonCost[i];//take away the cost of the button
							costText[i].setString("[Bought]");//display that it has been bought
							costText[i].setPosition(((400 - costText[i].getLocalBounds().width) / 2), ((i * 50) + 155));//centre the bought text where it should be
							break;
						case 1:
						case 3:
						case 5:
						case 7:
							available[i] = false;//set it to be false
							buttonUsed[i] = true;//set the next buttons availability to be true
							player.score -= buttonCost[i];//take away the cost of the button
							costText[i].setString("[Bought]");//display that it has been bought
							costText[i].setPosition((400 - costText[i].getLocalBounds().width) / 2 + 400, ((i - 1) * 50) + 155);//centre the bought text where it should be
							break;
						}

						switch (i)
						{
						case 0:
							std::cout << "Speed Increased" << std::endl;//display which upgrade was bought
							player.originalBearing += {0, -0.1, 0};//apply the upgrade
							player.bearing = player.originalBearing;//update the player bearing
							break;
						case 1:
							std::cout << "Speed Increased Again" << std::endl;//display which upgrade was bought
							player.originalBearing += {0, -0.1, 0};//apply the upgrade
							player.bearing = player.originalBearing;//update the player bearing
							break;
						case 2:
							std::cout << "Fuel Increased" << std::endl;//display which upgrade was bought
							player.originalFuel += 50;//apply the upgrade
							player.fuel = player.originalFuel;//update the players fuel
							player.fuelBar.setScale(.98, 1);//scaale the fuel bar
							break;
						case 3:
							std::cout << "Fuel Increased Again" << std::endl;//display which upgrade was bought
							player.originalFuel += 50;//apply the upgrade
							player.fuel = player.originalFuel;//update the players fuel
							player.fuelBar.setScale(.8, 1);//scaale the fuel bar
							break;
						case 4:
							std::cout << "Armour Increased" << std::endl;//display which upgrade was bought
							player.originalArmour += 30;//apply the upgrade
							player.armour = player.originalArmour;//update the player armour
							break;
						case 5:
							std::cout << "Armour Increased Again" << std::endl;//display which upgrade was bought
							player.originalArmour += 30;//apply the upgrade
							player.armour = player.originalArmour;//update the player armour
							break;
						case 6:
							std::cout << "Bullet Speed Increased" << std::endl;//display which upgrade was bought
							player.bulletSpeed -= 2;//update the players bullet speed
							break;
						case 7:
							std::cout << "Bullet Speed Increased Again" << std::endl;//display which upgrade was bought
							player.bulletSpeed -= 2;//update the players bullet speed
							break;
						case 8:
							Game::m_currentGameMode = GameStatus::MainMenu;//return to the main menu
							break;
						}

					}

				}
			}
			//loop for all buttons
			for (int i = 0; i < 9; i++)
			{
				//update the button and recentre them
				buttons[i].setSize(sizeVector);
				updateButtonPos(i);
			}

		}
	}
}

/// <summary>
/// Function to draw objects to window
/// </summary>
void HangarScreen::render()
{
	//draw the backgrond image
	Game::m_window.draw(m_backgroundSprite);
	//loop for all buttons
	for (int i = 0; i < HANGAR_MENU_MAX_BUTTONS; i++)
	{
		//draw the buttons and text
		Game::m_window.draw(buttons[i]);
		Game::m_window.draw(buttonTexts[i]);
		//for all buttons that hould have cost text
		if (i < HANGAR_MENU_MAX_BUTTONS - 1)
		{
			//draw cost text
			Game::m_window.draw(costText[i]);
		}
	}
	//draw other text objects
	Game::m_window.draw(m_titleText);
	Game::m_window.draw(m_scoreText);
}

/// <summary>
/// Set up buttons onscreen
/// </summary>
/// <param name="font"> font passed from main</param>
/// <param name="texture">spritesheet Passed from main</param>
void HangarScreen::initialiseButtons(sf::Font & font, sf::Texture &texture)
{
	//set up the background sprite
	m_backgroundSprite.setTexture(texture);
	m_backgroundSprite.setTextureRect(sf::IntRect(1503, 484, static_cast<int>(800), static_cast<int>(600)));//set the position of the image on the sprite sheet and the size of its rectangle
	m_backgroundSprite.setPosition(0, 0);
	m_backgroundSprite.setColor(sf::Color::Blue);

	//set up the title text 
	m_titleText.setString("Hangar");
	m_titleText.setFillColor(sf::Color::White);
	m_titleText.setCharacterSize(70);
	m_titleText.setFont(font);
	m_titleText.setPosition((800 - m_titleText.getLocalBounds().width) / 2, 10);

	//set up the score text
	m_scoreText.setString("Score: 0");
	m_scoreText.setFillColor(ASTEROIDTEXTCOLOUR);
	m_scoreText.setCharacterSize(30);
	m_scoreText.setFont(font);
	m_scoreText.setPosition((800 - m_scoreText.getLocalBounds().width) / 2, 80);

	//set up the button texts
	buttonTexts[0].setString("Speed 1");
	buttonTexts[1].setString("Speed 2");
	buttonTexts[2].setString("Fuel 1");
	buttonTexts[3].setString("Fuel 2");
	buttonTexts[4].setString("Armour 1");
	buttonTexts[5].setString("Armour 2");
	buttonTexts[6].setString("Bullet Speed 1");
	buttonTexts[7].setString("Bullet Speed 2");
	buttonTexts[8].setString("Return");

	//set up the cost texts
	costText[0].setString("(1000)");
	costText[1].setString("(1500)");
	costText[2].setString("(750)");
	costText[3].setString("(1500)");
	costText[4].setString("(1000)");
	costText[5].setString("(2000)");
	costText[6].setString("(600)");
	costText[7].setString("(1000)");

	//loop for all buttons
	for (int i = 0; i < HANGAR_MENU_MAX_BUTTONS; i++)
	{
		//set up the buttons
		buttons[i].setTexture(&texture);
		buttons[i].setTextureRect(sf::IntRect(1065, 0, static_cast<int>(320), static_cast<int>(75)));//set the position of the image on the sprite sheet and the size of its rectangle
		buttons[i].setSize(sizeVector);

		//set up the button texts
		buttonTexts[i].setFillColor(sf::Color::White);
		buttonTexts[i].setCharacterSize(25);
		buttonTexts[i].setFont(font);

		//set up the cost texts
		costText[i].setFillColor(ASTEROIDTEXTCOLOUR);
		costText[i].setCharacterSize(22);
		costText[i].setFont(font);

		//set the text positions
		setTextPos(i);
		updateButtonPos(i);//update the button position depending on the size vector
	}
}

/// <summary>
/// Update the button positinos when hovered over
/// </summary>
/// <param name="i">MaxButtons</param>
void HangarScreen::updateButtonPos(int i)
{
	//if button 0,2,4,6
	if (i == 0 || i == 2 || i == 4 || i == 6)
	{
		//centre the button appropriately
		buttons[i].setPosition(((400 - buttons[i].getLocalBounds().width) / 2), (i * 50) + 120);
	}
	//if button 1,3,5,7
	else if (i == 1 || i == 3 || i == 5 || i == 7)
	{
		//centre the button appropriately
		buttons[i].setPosition(((400 - buttons[i].getLocalBounds().width) / 2) + 400, ((i - 1) * 50) + 120);
	}
	//if button 8
	else if (i == 8)
	{
		//centre the button appropriately
		buttons[i].setPosition((800 - buttons[i].getLocalBounds().width) / 2, (i * 50) + 110);
	}

}

/// <summary>
/// set the positions of the text onjects
/// </summary>
/// <param name="i"></param>
void HangarScreen::setTextPos(int i)
{
	//if button text 0,2,4,6
	if (i == 0 || i == 2 || i == 4 || i == 6)
	{
		//centre the texts appropriately
		buttonTexts[i].setPosition(((400 - buttonTexts[i].getLocalBounds().width) / 2), (i * 50) + 130);
		costText[i].setPosition(((400 - costText[i].getLocalBounds().width) / 2), ((i * 50) + 155));
	}
	//if button text 1,3,5,7
	else if (i == 1 || i == 3 || i == 5 || i == 7)
	{
		//centre the texts appropriately
		buttonTexts[i].setPosition(((400 - buttonTexts[i].getLocalBounds().width) / 2) + 400, ((i - 1) * 50) + 130);
		costText[i].setPosition((400 - costText[i].getLocalBounds().width) / 2 + 400, ((i - 1) * 50) + 155);
	}
	//if button text 8
	else if (i == 8)
	{
		//centre the texts appropriately
		buttonTexts[i].setPosition((800 - buttonTexts[i].getLocalBounds().width) / 2, (i * 50) + 130);
	}
}


