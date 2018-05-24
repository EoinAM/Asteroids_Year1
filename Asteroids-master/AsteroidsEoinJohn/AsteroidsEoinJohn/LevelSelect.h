#ifndef LEVEL_SELECT
#define LEVEL_SELECT
#include "SFML\Graphics.hpp"
#include "MyVector3D.h"
#include "Asteroid.h"
#include "Player.h"

#include "Gems.h"

const sf::Color PLAYABLE_BLUE(23, 118, 196, 255); //Blue color if game is playable
const static int MAX_BUTTONS{ 9 };/// Max buttons on level select screen

class LevelSelectScreen
{
public:
	LevelSelectScreen(sf::Font & font, sf::Texture & texture);//overloaded constructor
	~LevelSelectScreen();//default destructor
	void initialiseButtons(sf::Font & font, sf::Texture &texture);//set up the buttons and text objects
	void processEvents(sf::Event event, Asteroid asteroid[], int MAX_ASTEROIDS, bool levelActive[], Player &player, bool &gameOver, Gems gemArray[]);//process player input and reset the game fresh
	void update(bool levelActive[]);//update the buttons
	void render();//render the level select variables

private:
	void updateButtonPos(int i);//update the button position to centre it when the size vector is changed
	void setTextPos(int i);////set the positions of the texts
public:
	sf::RectangleShape buttons[MAX_BUTTONS];// array of rectangles to be used as buttons
	sf::Text buttonText[MAX_BUTTONS];// array of text for buttons
	sf::Text m_titleText;// Level Select title at top of screen
	sf::Sprite m_levelSelectSprite;// Background image sprite
private:
	MyVector3D sizeVector{ 200,150,0 };// button size vector
	MyVector3D buttonChange{ 224,151,0 };// button size when hovered over
	const sf::Color ASTEROIDTEXTCOLOUR{ 1, 143, 200, 255 };// Blue color for text
	int asteroidNumber[MAX_BUTTONS] = {3,5,6,7,8,10,10,11,11};//the number of asteroids to be spawned each level
};


#endif