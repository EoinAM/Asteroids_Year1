#ifndef MAIN_MENU
#define MAIN_MENU

#include "SFML\Graphics.hpp"
#include "MyVector3D.h"
class Main
{
public: //functions
	Main(sf::Font & font, sf::Texture & texture);//overloaded constructor
	~Main();//default destructor
	void update();//update mainmenu variables
	void processEvents(sf::Event event);//process user input
	void render();//draw objects to the screen

private: //functions
	void initialiseButtons(sf::Font &font, sf::Texture & texture);//set up the buttons and button texts
	void updateButtonPos(int i);//update the button position if the size vector has been changed

public: //objects
	//Max Buttons on main menu
	static const int MAIN_MENU_MAX_BUTTONS{ 4 };
	//array of rectangles to be used as button
	sf::RectangleShape buttons[MAIN_MENU_MAX_BUTTONS];
	//array of Text for buttons
	sf::Text buttonText[MAIN_MENU_MAX_BUTTONS];
	//Android Text at the top of the screen
	sf::Text m_titleText;
	//backgrouund Sprite
	sf::Sprite m_menuSprite;
	//Menu buttons sprite
	sf::Sprite m_menuButtonSprite;

private: //objects
	//Asteroid Color
	const sf::Color ASTEROIDTEXTCOLOUR{ 1, 143, 200, 255 };
	//Button Size
	MyVector3D sizeVector{ 400,70,0 };
	//Button size when hovered over
	MyVector3D buttonChange{ 428,71,0 };
};
#endif