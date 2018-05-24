	#ifndef PAUSE_MENU
#define PAUSE_MENU
#include "SFML\Graphics.hpp"
#include "MyVector3D.h"
#include "Player.h"
#include "Asteroid.h"
class PauseMenu
{
public:
	PauseMenu(sf::Font & font, sf::Texture & texture);//overloaded constructor
	~PauseMenu();//default destructor
	void processEvents(sf::Event event);//process user input
	void update();//update button variables
	void render();//draw the pause menu screen
private:
	void initialiseButtons(sf::Font & font, sf::Texture & texture);//set up the buttons and text
	void updateButtonPos(int i);//update the buttons positions
public:
	//Max buttons value
	static const int MAX_BUTTONS{ 3 };
	//Pause text at top of screen
	sf::Text m_titleText;
	//array of text for buttons
	sf::Text buttonText[MAX_BUTTONS];
	//array of rectangle shapes
	sf::RectangleShape buttons[MAX_BUTTONS];
private:
	//button size
	MyVector3D sizeVector{ 400,75,0 };
	//Button size when button is hovered over
	MyVector3D buttonChange{ 428,76,0 };
	//preset color for text
	const sf::Color ASTEROIDTEXTCOLOUR{ 1, 143, 200, 255 };
};


#endif