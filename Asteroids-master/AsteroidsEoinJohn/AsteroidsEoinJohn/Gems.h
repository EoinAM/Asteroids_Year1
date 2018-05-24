#ifndef GEMS
#define GEMS

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "MyVector3D.h"

class Gems
{
public:
	Gems(sf::Texture &texture);//overloaded constructor
	~Gems();//default destructor

	void render();//draw the gem object
	void reset();//reset the gem object
private:

public:
	sf::CircleShape body;//gem body
	sf::Texture gemTexture;//texture to be put on the gem body

	MyVector3D position{ 0,0,0 };//position of the gem

	bool isActive{ false };//wether the gem is alive or not
	double radius{ 20 };//raidius of the gem
};


#endif // !GEMS
