#ifndef HANGAR
#define HANGAR
#include "SFML\Graphics.hpp"
#include "MyVector3D.h"
#include "Player.h"
class HangarScreen
{
public:
	HangarScreen(sf::Font & font, sf::Texture & texture);//overloaded constructor 
	~HangarScreen();//default destructor
	void update(Player player);  //update hangar variables, player is passed so some player variables can be changed when the upgrades are selected
	void processEvents(sf::Event event, Player &player);//process player imput
	void render();//draw the hangar screen objects
private:
	void initialiseButtons(sf::Font &font, sf::Texture &texture);//set up the buttons and text objects
	void updateButtonPos(int i);//change the button positions whent he size is changed
	void setTextPos(int i);//set the positions of the text objects
public:
	static const int HANGAR_MENU_MAX_BUTTONS{ 9 };// Constant for maximum buttons
	sf::RectangleShape buttons[HANGAR_MENU_MAX_BUTTONS]; //Array of rectangles to be used as buttons
	bool available[HANGAR_MENU_MAX_BUTTONS], buttonUsed[HANGAR_MENU_MAX_BUTTONS - 1]; //bools to set if buttons can be used or not
	sf::Text buttonTexts[HANGAR_MENU_MAX_BUTTONS]; //array of text for buttons
	sf::Text costText[HANGAR_MENU_MAX_BUTTONS]; //array of Text to display prices
	sf::Text m_titleText; //Text to display "Hangar"
	sf::Text m_scoreText; //Text to show how many gems the player has
	int buttonCost[8] = { {1000},{1500},{750},{1500},{1000},{2000},{600},{1000} }; // Array of button costs to bepassed to text array
	sf::Sprite m_backgroundSprite; //Background image sprite
private:
	const sf::Color ASTEROIDTEXTCOLOUR{ 1, 143, 200, 255 }; //Constant for blue color
	MyVector3D sizeVector{ 320,75,0 }; //Size of the buttons
	MyVector3D buttonChange{ 344,76,0 }; //Size of button when hovered over
};


#endif