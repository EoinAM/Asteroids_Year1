#ifndef PLAYER
#define PLAYER
#include "SFML\Graphics.hpp"
#include "MyVector3D.h"
#include "Bullet.h"

//preset color for fuel bar
const sf::Color FUEL_COLOR{ 79, 235, 233, 255 };
//max bullets player can shoot 
const int MAX_BULLETS{ 12 };
class Player
{
public:
	Player(sf::Texture & texture);//overloaded constructor
	~Player();//default destructor
	void update();//update player variables
	void render();//render player objects
	void reset();//reset the player at the start of a new level

private:
	void move();//update the player positions
	void rotate(float angle);//rotate the player
	void playSounds();//play the player sounds
	void checkRotate();//check player rotate input
	void bulletCheck();//check plyaer bullet shoot inpout
	void armourCheck();//check player armour input

public:
	//Circle used as base body shape
	sf::CircleShape body;
	//radius of the player
	double radius{ 50 };
	//player's Velocity
	MyVector3D velocity{ 0,0,0 };
	//positions of the player
	MyVector3D originalPosition{ 360,260,0 }, position = originalPosition;
	MyVector3D originalBearing{0,-0.1,0};
	MyVector3D bearing = originalBearing;
	//Set shield to players position
	MyVector3D shielPos = position;
	//set fuel and armour starting values
	int originalFuel = 180, fuel = originalFuel, originalArmour = 180, armour = originalArmour, score = 0;
	//bools for if player  & armour is alive
	bool isAlive = true, armourActive = false;

	//bullet setup
	int bulletTimer{ 0 }, bulletSpeed{ 10 };
	
	//fuel UI
	sf::RectangleShape fuelBar;
	//circle shape for shield
	sf::CircleShape shieldbody;
	//radius of shield
	double shieldRadius{ 60 };

	//Time to ensure you dont die when you first spawn in 
	int safetyTimer{ 120 };

	//Sound items
	sf::SoundBuffer playerBuffer; //Sound buffer for engine sound
	sf::SoundBuffer shieldBuffer; //sound buffer for shield sound
	sf::Sound engineSound; //Engine sound file
	sf::Sound shieldSound; //Shield sound file
	bool engineSoundActive{ false }; //bool for if the engine is active
	bool shieldSoundActive{ false }; //bool for if the shield is active

	//array of bullets
	Bullet bullets[MAX_BULLETS];
	int counter{0};
};

#endif
