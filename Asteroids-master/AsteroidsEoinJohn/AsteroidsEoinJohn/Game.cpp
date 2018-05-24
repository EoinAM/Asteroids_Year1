#include "Game.h"

//static memebers o fhte game class that can be accessed outside of the game class
//gamemode variables
GameStatus Game::m_currentGameMode = GameStatus::License;
GameStatus Game::m_previousGameMode;

//variables to do wiutht he asteroids
int Game::startingAsteroids;
int Game::activeLevel;
bool Game::levelPlayable[MAX_BUTTONS] = { true,false,false,false,false,false,false,false,false };
ParticleSystem Game::particleEffects[10];

//render window
sf::RenderWindow Game::m_window(sf::VideoMode(800, 600), "Asteroids By Eoin And John");

/// <summary>
/// overloaded constructor for the game class
/// </summary>
/// <param name="font">default font to be used in all overloaded constructors for other objects in a game object</param>
/// <param name="texture">default texture sheet to be used in all overloaded constructors for other objects in a game object</param>
Game::Game(sf::Font & font, sf::Texture & texture) :
	//overloaded constructor of objects withing the game class
	//screens
	m_licenseScreen(font, texture),
	
	m_mainMenu(font, texture),
	m_helpScreen(font, texture),
	m_hangarScreen(font, texture),
	m_levelSelectScreen(font, texture),
	m_pauseScreen(font, texture),
	m_splashScreen(font, texture),

	//player, asteroids, gems
	player(texture),
	asteroid{ (texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture),
	(texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture) },
	gemArray{ (texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture),
	(texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture),(texture) ,(texture) ,(texture) ,(texture),(texture) }
{
	//set up the backgound sprite
	backgroundSprite.setTexture(texture);
	backgroundSprite.setPosition(0, 0);//set the position it draws from
	backgroundSprite.setTextureRect(sf::IntRect(0, 1084, static_cast<int>(800), static_cast<int>(600)));//position of the image in the sprite sheet and the size of the rectangle containing the image

	//set up UI sprite
	ScreenUI.setTexture(texture);
	ScreenUI.setPosition(10, 470);//set the position it draws from
	ScreenUI.setTextureRect(sf::IntRect(800, 1684, static_cast<int>(1132), static_cast<int>(348)));//position of the image in the sprite sheet and the size of the rectangle containing the image
	ScreenUI.setScale(.35, .35);//change the size of the image

	//set up score text
	scoreText.setFont(font);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setCharacterSize(31);
	scoreText.setString("G.E.M.S :" + std::to_string(player.score));//set the string
	scoreText.setPosition(600, 507);//set the position

	//set up level end notification text
	gameOverText.setFont(font);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setCharacterSize(30);
	gameOverText.setString("");//set to be an empty string
	gameOverText.setPosition(75, 75);//set the position

	//set up the armour text
	armourText.setFont(font);
	armourText.setFillColor(sf::Color::White);
	armourText.setCharacterSize(31);
	armourText.setString(std::to_string(player.armour));//set the string
	armourText.setPosition(48, 507);//set the position

	if (!playingBuffer.loadFromFile("ASSETS\\Sounds\\GameMusic.wav"))
	{
		std::cout << "Game music not loaded" << std::endl;
	}
	gameMusic.setBuffer(playingBuffer);
	gameMusic.setVolume(5);
	gameMusic.setLoop(true);
}

/// <summary>
/// default destructor
/// </summary>
Game::~Game()
{
} 

/// <summary>
/// contains the game loop
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	//while the windopw is open loop around
	while (m_window.isOpen())
	{
		processEvents();//call the process events function
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			//update the game exactly 60 times per second
			if (timeSinceLastUpdate > timePerFrame)
			{
				update(timePerFrame);//call the update function
			}
			timeSinceLastUpdate -= timePerFrame;
			processEvents();//call the process events function
		}
		render();//call the render function
	}
}

/// <summary>
/// process any of the user input, call each objects processEvents function accordingly
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		//if the x is pressed on the window the window will close and the programme will stop
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		//if the semicolon key is pressed allow the user to input a cheatcode
		/// <summary>
		/// Superman
		/// Motherlode
		/// Deadstroid
		/// Fuelled
		/// </summary>
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon))
		{
			debugCmdLine();
		}

		//depending on the gamemode, process the corresponding events
		switch (m_currentGameMode)
		{
		case License:
		{
			break;
		}
		case Splash:
		{
			m_splashScreen.processEvents(event);
			break;
		}
		case MainMenu:
		{
			m_mainMenu.processEvents(event);
			break;
		}
		case LevelSelect:
		{
			//pass the player object, asteroid array, the max number of asteroids, game over and the gems array, aswell as the event
			m_levelSelectScreen.processEvents(event, asteroid, MAX_ASTEROIDS,levelPlayable, player, gameOver,gemArray);
			break;
		}
		case Playing:
		{
						
			//if the escape key is pressed enter the pause menu
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				Game::m_currentGameMode = GameStatus::Pause;
			}
			break;
		}
		case HelpMenu:
		{
			m_helpScreen.processEvents(event);
			break;
		}
		case Hangar:
		{
			//pass the player object so it can be upgraded inside the hangar
			m_hangarScreen.processEvents(event, player);
			break;
		}
		case Pause:
		{
			m_pauseScreen.processEvents(event);
			break;
		}
		}
	}
}

/// <summary>
/// update all of the objects, text and check for anything that needs to be changed each frame
/// </summary>
/// <param name="time">the amount of time since the last frame</param>
void Game::update(sf::Time time)
{
	playSounds(); //check what sounds are to be played

	//depending on the game mode update the appropriate objects
	//each object has its own update function
	switch (m_currentGameMode)
	{
	case License:
	{
		m_licenseScreen.update(time);
		break;
	}
	case Splash:
	{
		m_splashScreen.update(time);
		break;
	}
	case MainMenu:
	{
		
		m_mainMenu.update();
		break;
	}
	case LevelSelect:
	{
		m_levelSelectScreen.update(levelPlayable);
		break;
	}
	case Playing:
	{
		//update UI text
		userInterfaceTextUpdate();
		//check if you win the game
		checkGameWin();
		
		//update the particle systems
		for (int i = 0; i < 10; i++)
		{
			particleEffects[i].update();
		}
		if (!player.isAlive)
		{
			player.shieldSound.stop();
			player.engineSound.stop();
			player.shieldSoundActive = false;
			player.engineSoundActive = false;
		}
		//update the player if it is alive
		if (player.isAlive)
		{
			player.update();
		}	

		//if the superman cheat is turned on dont check if the player collides with an asteroid
		if (activeCheatCode == "Superman")
		{
		}
		else
		{
			shipAsteroidCollision();//check ship asteroid collision
		}
			
		shipGemCollision();//check if the player collides with any gems
		bulletAsteroidCollision();//check if the bullet collides with any ateroids

		//loop through all of the bullets
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			//if the bullet is alive update its position
			if (player.bullets[i].isActive)
			{
				player.bullets[i].move();
			}
		}

		//loop throuhg all of the asteroids
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			//if the cheat deadstroid is active break out of the loop
			if (activeCheatCode == "Deadstroid")
			{
				break;
			}
			//if the asteroid is alive, update its position
			asteroid[i].update();
		}

		break;
	}
	case HelpMenu:
	{
		m_helpScreen.update();
		break;
	}
	case Hangar:
	{
		m_hangarScreen.update(player);
		break;
	}
	case Pause:
	{
		m_pauseScreen.update();
		break;
	}
	}
}

/// <summary>
/// check if the player has collided with a gem
/// </summary>
void Game::shipGemCollision()
{
	//loop through all of the gems
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		//if the gem is alive
		if (gemArray[i].isActive)
		{
			//and the player is alive
			if (player.isAlive)
			{
				//check if the distance between their centres is less than the radii
				if ((gemArray[i].position - player.position).length() <= (player.radius * .9) + gemArray[i].radius * .9)
				{
					player.score += 150; //add 100 onto the players score
					gemArray[i].reset();//reset the gem
				}
			}
		}
	}
}

/// <summary>
/// check if the player has collided with an asteroid
/// </summary>
void Game::shipAsteroidCollision()
{
	//loop through all of the asteroids
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		//if the player is alive and the initial safety period has passed
		if (player.isAlive && player.safetyTimer == 0)
		{
			//check if the asteroid is alive
			if (asteroid[i].isAlive)
			{
				//check if the distance between the centres is less than the sum of the radii
				if ((asteroid[i].position - player.position).length() <= (player.radius * .9) + asteroid[i].radius * .9)
				{
					//if the players armour isnt active
					if (!player.armourActive)
					{
						player.shieldSoundActive = false;
						player.engineSoundActive = false;
						player.isAlive = false;//set teh player to be dead
						gameOverText.setString("							Hard Luck \nHeadback to the level select And Try Again");//change the game over textr
						gameOverText.setPosition((800 - gameOverText.getLocalBounds().width) / 2, gameOverText.getPosition().y);
						gameOver = true;//set the game over to be true
						break;
					}
				}
			}
		}
	}
}

/// <summary>
/// check if the bullet has collided with an asteroid
/// </summary>
void Game::bulletAsteroidCollision()
{
	bool found = false;//bool to allow the breaking out of nested loop

	//loop through all of the bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		//if the bullet is alive
		if (player.bullets[i].isActive)
		{
			//loop through all of the asteroids
			for (int j = 0; j < MAX_ASTEROIDS; j++)
			{
				//if the asteroid is alive
				if (asteroid[j].isAlive)
				{
					//if the bullet enters the asteroid
					if(player.bullets[i].position.X() <= (asteroid[j].position.X() + (asteroid[j].radius * .9)) && player.bullets[i].position.X() >= (asteroid[j].position.X() - (asteroid[j].radius * .9))
						&& player.bullets[i].position.Y() <= (asteroid[j].position.Y() + (asteroid[j].radius * .9)) && player.bullets[i].position.Y() >= (asteroid[j].position.Y() - (asteroid[j].radius * .9)))
					{
						//reset and turn on a particle effect
						particleEffects[activeParticle].initialise(asteroid[j].position);
						
						//if the last particle was active loop back to the 0 element
						asteroid[j].asteroidBreak.play();
						if (activeParticle == 9)
						{
							activeParticle = 0;
						}
						//otherwise increment
						else
						{
							activeParticle++;
						}

						player.bullets[i].isActive = false;//set the bullet alive to be false
						asteroid[j].isAlive = false;//set the asteroid to be false
						asteroidSplit(j);//call the asteroidSplit function and pass the current asteroid array element number


						//if the asteroid has a gem availabel to it
						if (asteroid[j].isGemAvailable)
						{
							//loop through all of the gems
							for (int k = 0; k < MAX_ASTEROIDS; k++)
							{
								//if the gem is not active
								if (gemArray[k].isActive == false)
								{
									gemArray[k].position = asteroid[j].position;//set its position to be the asteroids position
									gemArray[k].body.setPosition(gemArray[k].position);//set its body position to be its position
									gemArray[k].isActive = true;//set the gem to be active
									break; //break out of the loop
								}
							}
						}

						found = true;//set the found bool to be true
						break;
					}
				}
				//if the bullet collided with something (found) then break out of the outer loop
				if (found)
				{
					break;
				}
			}
		}
	}
}


/// <summary>
/// updates the armour and gems text and changes their colours as needed
/// </summary>
void Game::userInterfaceTextUpdate()
{
	//set the strings
	scoreText.setString("G.E.M.S : " + std::to_string(player.score));
	if (player.armour < 10)
	{
		armourText.setString(" " + std::to_string(player.armour));
	}
	else
	{
		armourText.setString(std::to_string(player.armour));
	}

	//if the armour is above 40 then set it to green when it is active
	if (player.armourActive)
	{
		if (player.armour >= 40)
		{
			armourText.setFillColor(sf::Color::Green);
		}
	}
	//if the armour isnt active set it to white
	else
	{
		armourText.setFillColor(sf::Color::White);
	}

	//if the armour gets below 40 set it to red
	if (player.armour < 40)
	{
		armourText.setFillColor(sf::Color::Red);
	}
}

/// <summary>
/// take input from the user in the command window if the semicolon was pressed
/// </summary>
void Game::debugCmdLine()
{
	//put the input word into the activeCheatCode variable
	std::cin >> activeCheatCode;

	//if the cheat is motherlode
	if (activeCheatCode == "Motherlode")
	{
		//add 5000 to the players score
		player.score += 5000;
	}

	//if the cheat is fuelled
	if (activeCheatCode == "Fuelled")
	{
		//add 150 to the player fuel
		player.fuel += 150;
	}


	//set all asteroids o be false if kill
	if (activeCheatCode == "Kill")
	{
		//loop through all asteroids setting them to be false
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			asteroid[i].isAlive = false;
		}
	}

	//if the cheat is unlock
	if (activeCheatCode == "Unlock")
	{
		//set all levels to be available
		for (int i = 0; i < 9; i++)
		{
			levelPlayable[i] = true;
		}

	}
}

/// <summary>
/// function to call all objects render functions
/// </summary>
void Game::render()
{
	m_window.clear();//clear the window

	//depending on the game mode call the appropriate renbder functions
	switch (m_currentGameMode)
	{
	case License:
	{
		m_licenseScreen.render();
		break;
	}
	case Splash:
	{
		m_splashScreen.render();
		break;
	}
	case MainMenu:
	{
		m_mainMenu.render();
		break;
	}
	case LevelSelect:
	{
		m_levelSelectScreen.render();
		break;
	}
	case Playing:
	{
		m_window.draw(backgroundSprite);//draw the background image

		//loop though all of the gems and asteroids
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			//if a gem is active draw it
			gemArray[i].render();
			//if an asteroid is active draw it
			asteroid[i].render();
		}
		//render the player
		player.render();

		//loop through all of the particle effects
		for (int i = 0; i < 10; i++)
		{
			particleEffects[i].render();
		}
	
		//if the game has ended
		if (gameOver)
		{
			//draw the game over message
			m_window.draw(gameOverText);
		}

		//draw the screen UI and UI messages
		m_window.draw(ScreenUI);
		m_window.draw(scoreText);
		m_window.draw(player.fuelBar);
		m_window.draw(armourText);

		break;
	}
	case HelpMenu:
	{
		m_helpScreen.render();
		break;
	}
	case Hangar:
	{
		m_hangarScreen.render();
		break;
	}
	case Pause:
	{
		m_window.draw(backgroundSprite);//draw the background image

										//loop though all of the gems and asteroids
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			//if a gem is active draw it
			gemArray[i].render();
			//if an asteroid is active draw it
			asteroid[i].render();
		}
		//render the player
		player.render();

		//loop through all of the particle effects
		for (int i = 0; i < 10; i++)
		{
			particleEffects[i].render();
		}

		m_pauseScreen.render();
		break;
	}
	}
	m_window.display();//output the render screen
}

/// <summary>
/// if the asteroid has been hit by a bullet it should split into more asteroids
/// </summary>
/// <param name="number">the asteroid element number that was hit by the asteroid</param>
void Game::asteroidSplit(int number)
{
	MyVector3D tempPos = asteroid[number].position;//variable to hold the position where the asteroid that died was

	//depending on what sizethe asteroid was, create a different number of new asteroids of one size smaller
	switch (asteroid[number].currentSize)
	{
		//if it was a big asteroid
	case big:
		asteroidSplitCounter = rand() % 2;//create up to two new ones

		//loop through all of the asteroids
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			//if the asteroid isnt alive
			if (!asteroid[i].isAlive)
			{
				//if the number of new asteroids still to be created is created than 0
				if (asteroidSplitCounter > 0)
				{
					asteroid[i].reset(1, tempPos);//reset the asteroid using an overloaded function
					asteroidSplitCounter--;//reduce the number of new asteroids still to be created
				}
				else
				{
					break;
				}
			}
		}

		break;
	case medium:
		asteroidSplitCounter = rand() % 3;//create  up to three new ones

		//loop through all of the asteroids
		for (int i = 0; i < MAX_ASTEROIDS; i++)
		{
			//if the asteroid isnt alive
			if (!asteroid[i].isAlive)
			{
				//if the number of new asteroids still to be created is created than 0
				if (asteroidSplitCounter > 0)
				{
					asteroid[i].reset(2, tempPos);//reset the asteroid using an overloaded function
					asteroidSplitCounter--;//reduce the number of new asteroids still to be created
				}
				else
				{
					break;
				}
			}
		}

		break;
	}
}

/// <summary>
/// check if the player has won the game
/// </summary>
void Game::checkGameWin()
{
	//reset the counter of living asteroids
	livingAsteroids = 0;

	//loop through all of the asteroids checking if they are alive
	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		//if they are alive add 1 onto the living asteroids
		if (asteroid[i].isAlive)
		{
			livingAsteroids++;
		}
	}

	//if there are no living asteroids set game over to be true and change the level end notificaation text
	if (livingAsteroids == 0)
	{
		gameOverText.setString("							Congratulations \nCollect your loot and headback to the level select");
		gameOverText.setPosition((800 - gameOverText.getLocalBounds().width) / 2, gameOverText.getPosition().y);
		gameOver = true;
		levelPlayable[activeLevel] = true;//set the next level to be playable
	}
}

/// <summary>
/// Function to check when the menu music should be played and when to play the license sound
/// </summary>
void Game::playSounds()
{
	//If gamemode is on playing or pause screen
	if (Game::m_currentGameMode == GameStatus::Playing || Game::m_currentGameMode == GameStatus::Pause)
	{
		//if menu music is playing
		if (m_splashScreen.backgroundMusic.getStatus() == sf::SoundSource::Playing)
		{	//stop menu music
			m_splashScreen.backgroundMusic.stop();
		}
		//if gamemusic isn't playing
		if (gameMusic.getStatus() == !sf::SoundSource::Playing)
		{	//play game music
			gameMusic.play();
		}
		
	}
	else //if onany other screen
	{
		//if game music is playing
		if (gameMusic.getStatus() == sf::SoundSource::Playing )
		{	
			gameMusic.stop();// stop gamemusic
		}
		//if menu music is playing
		if (m_splashScreen.backgroundMusic.getStatus() == !sf::SoundSource::Playing)
		{
			m_splashScreen.backgroundMusic.play();//stop menu music
		}
	}

}
