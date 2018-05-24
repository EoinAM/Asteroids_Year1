#ifndef GAME
#define GAME
#ifndef SFML_STATIC


#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
//#pragma comment(lib,"sfml-main-d.lib")
//#pragma comment(lib,"sfml-network-d.lib")

#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-audio.lib")
//#pragma comment(lib,"sfml-main.lib")
//#pragma comment(lib,"sfml-network.lib")
#endif //_DEBUG
#else
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-s-d.lib")
#pragma comment(lib,"freetype.lib")
#pragma comment(lib,"jpeg.lib")
#pragma comment(lib,"opengl32.lib")

#pragma comment(lib,"sfml-system-s-d.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"sfml-window-s-d.lib")
#pragma comment(lib,"winmm")
#pragma comment(lib,"gdi32")

#pragma comment(lib,"sfml-audio-s-d.lib")
#pragma comment(lib,"flac.lib")
#pragma comment(lib,"ogg.lib")
#pragma comment(lib,"vorbisenc.lib")
#pragma comment(lib,"vorbisfile.lib")
#pragma comment(lib,"vorbis.lib")
#pragma comment(lib,"openal32.lib")
//#pragma comment(lib,"sfml-main-s-d.lib")
//#pragma comment(lib,"sfml-network-s-d.lib")
//#pragma comment(lib,"ws2_32.lib")

#else
#pragma comment(lib,"sfml-graphics-s.lib")
#pragma comment(lib,"freetype.lib")
#pragma comment(lib,"jpeg.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"sfml-system-s.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"sfml-window-s.lib")
#pragma comment(lib,"winmm")
#pragma comment(lib,"gdi32")
#pragma comment(lib,"sfml-audio-s.lib")
#pragma comment(lib,"flac.lib")
#pragma comment(lib,"ogg.lib")
#pragma comment(lib,"vorbisenc.lib")
#pragma comment(lib,"vorbisfile.lib")
#pragma comment(lib,"vorbis.lib")
#pragma comment(lib,"openal32.lib")
//#pragma comment(lib,"sfml-main-s.lib")
//#pragma comment(lib,"sfml-network-s.lib")
//#pragma comment(lib,"ws2_32.lib")
#endif //_DEBUG
#endif // !SFML_STATIC 

#include<SFML\Graphics.hpp>
#include <iostream>
#include "License.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Help.h"
#include "HangarScreen.h"
#include "LevelSelect.h"
#include "Pause.h"
#include "Player.h"
#include "Asteroid.h"
#include "MyVector3D.h"
#include "Gems.h"
#include "ParticleSystem.h"

enum GameStatus
{
	License,
	Splash,
	MainMenu,
	LevelSelect,
	Playing,
	HelpMenu,
	Hangar,
	Pause
};

class Game
{
public:
	Game(sf::Font & font, sf::Texture & texture);//overloaded constructor
	~Game();//default destructor
	void run();//gameloop function

private:
	//main functions
	void processEvents();//process user input
	void update(sf::Time time);//update the game 60 times per second
	void render();//draw everything to the screen

	//gameplay functions
	void asteroidSplit(int number);//split into more asteroids when hit
	void shipAsteroidCollision();//check if the ship collides with an asteroid
	void bulletAsteroidCollision();//check if a bullet collides with an asteroid
	void shipGemCollision();//check if the ship collides with a gem
	void userInterfaceTextUpdate();//update the user interface text
	void debugCmdLine();//cheat input
	void checkGameWin();//count how many asteroids are alive
	void playSounds(); //switch between game and menu sounds

public:
	//static variables
	static sf::RenderWindow m_window;//game window
	static GameStatus m_currentGameMode;//what game mode the game is currently in
	static GameStatus m_previousGameMode;//used to transition from help menu to the pause menu or to the main menu correctly
	static int startingAsteroids;//how many asteroids start each level
	static int activeLevel;//which level is currently active
	static bool levelPlayable[MAX_BUTTONS];//wether a level is playable or not
	static ParticleSystem particleEffects[10];//array of particle effects
	
private:
	//screen objects
	license m_licenseScreen;
	Main m_mainMenu;
	splash m_splashScreen;
	HelpScreen m_helpScreen;
	HangarScreen m_hangarScreen;
	LevelSelectScreen m_levelSelectScreen;
	PauseMenu m_pauseScreen;

	//UI Objects
	sf::Sprite backgroundSprite;//gameplay screen background image
	sf::Sprite ScreenUI;//the users interface image in the bottom right of the screen
	std::string activeCheatCode;// = "Superman";
	sf::Text armourText;//text to display the armour the user has left
	sf::Text scoreText;//the player score

	//gameOver variables
	sf::Text gameOverText;//text displayed at the end of a game
	bool gameOver{ false };//wether the game has ended

	int activeParticle{ 0 };//which particle is active

	//player object and variables
	Player player;//player object
	static const int MAX_ASTEROIDS = 40;//the ax number of asteroids allowed in a game screen at any one time
	Asteroid asteroid[MAX_ASTEROIDS];//array of asteroid objects
	Gems gemArray[MAX_ASTEROIDS];//array of gem objects
	
	int livingAsteroids;//used to count how many asteroids are alive each update to determine if the game has ended
	int asteroidSplitCounter = 0;//number of asteroids to be created once an asteroid collides with a bullet(randomly generated)
	sf::SoundBuffer playingBuffer; //Buffer for level playing
	sf::Sound gameMusic; //backgroundmusic for game
};
#endif