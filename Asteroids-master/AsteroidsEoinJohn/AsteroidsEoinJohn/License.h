#ifndef LICENSE
#define LICENSE

#include <SFML\Graphics.hpp>
#include "MyVector3D.h"
class license
{
public: //functions
	license(sf::Font & font, sf::Texture & texture);//overloaded constructor
	~license();//default destructor

	void update(sf::Time time);//update the license screen variables
	void render();//draw the license screen objects
private: //funtions

public: //objects
	
	// License screen Messages
	sf::Text m_licenseMessage;
	// License screen background image
	sf::Sprite m_licenseSprite;
	sf::Sprite m_JellySprite;
	
private: //objects
	// Time sprite to track how long has passed to change which screen is active
	sf::Time m_cumulativeTime{ sf::Time::Zero };
	// preset text color
	const sf::Color TEXTCOLOUR{ 1, 13, 48, 255 };

};
#endif // !LICENSE

