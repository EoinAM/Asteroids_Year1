#ifndef HELP_MENU
#define HELP_MENU
#include "SFML\Graphics.hpp"
#include "MyVector3D.h"
class HelpScreen
{
public:
	HelpScreen(sf::Font & font, sf::Texture & texture);//overloaded consturctor
	~HelpScreen();//default destructor
	void processEvents(sf::Event event);//process player input
	void update();//update help menu variables
	void render();//render the help menu objects
private:
	void initialiseText(sf::Font & font, sf::Texture &texture);//set up the help menu text
	void updateButtonPos();//update the button position
public:
	sf::Text m_helpText;// In game instructions title at top of screen

private:
	sf::RectangleShape m_button;// Button shape
	MyVector3D sizeVector{ 320, 75,0 };// Size vector for button
	MyVector3D buttonScale{ 344,76,0 };// Size of button when hovered over
	sf::Sprite m_background;// Background image
	sf::Text m_buttonText;// Text on button
	sf::Texture m_backgroundTexture;// Texture for background image
};


#endif