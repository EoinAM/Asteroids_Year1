/// <summary>
/// @Authors Eoin Abbey-Maher & John Foley
/// @date 21-02-17
/// 
/// </summary>

#ifndef SPLASH
#define SPLASH
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "MyVector3D.h"
class splash
{
public: //Functions
	splash(sf::Font & font, sf::Texture & texture);//overloaded constructor
	~splash();//default destructor
	void processEvents(sf::Event);//process events
	void update(sf::Time time);//update the splash screen
	void render();//reder the spplashscreen object
private: //functions
	void initialiseText(sf::Font &font);//set up the text objects

public: //objects
	//splash screen message
	sf::Text m_splashMessage;
	//splash screen background
	sf::Sprite m_splashSprite;
	//Buffer for menu music
	sf::SoundBuffer gameBuffer;
	//menu background music
	sf::Sound backgroundMusic;
	//preset colours that flashing text switches between
	const sf::Color TEXTCOLOUR1{ 1, 13, 48, 255 };
	const sf::Color TEXTCOLOUR2{ 1, 52, 103,255 };

private: //objects
	//bool to take you to next screen
	bool m_proceed{ false };
	
	//flash timer
	sf::Time m_cumulativeTime{ sf::Time::Zero };
	
};
#endif // !SPLASH
