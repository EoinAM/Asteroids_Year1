#include "Player.h"
#include "Game.h"
#include <iostream>

/// <summary>
/// overloaded constructor
/// </summary>
/// <param name="texture">sprite sheet</param>
Player::Player(sf::Texture & texture)
	:
	//overload the bullet constructors
	bullets{ (texture) , (texture) , (texture) , (texture), (texture) , (texture) , (texture), (texture), (texture), (texture), (texture), (texture) }
{
	//set up the body
	body.setRadius(radius);
	body.setPosition(position);
	body.setTexture(&texture);
	body.setTextureRect(sf::IntRect(765, 0, static_cast<int>(300), static_cast<int>(300)));//set the position of the image on the sprite sheet and the size of its rectangle
	body.setOrigin(radius, radius);

	//set up the shield
	shieldbody.setRadius(shieldRadius);
	shieldbody.setPosition(shielPos);
	shieldbody.setOrigin(shieldRadius, shieldRadius);
	shieldbody.setTexture(&texture);
	shieldbody.setTextureRect(sf::IntRect(1705, 0, static_cast<int> (484), static_cast<int>(484)));//set the position of the image on the sprite sheet and the size of its rectangle

	//set up the fuel bar
	fuelBar.setSize(sf::Vector2f(fuel, 30));
	fuelBar.setScale(1.23, 1);
	fuelBar.setOutlineColor(sf::Color::White);
	fuelBar.setOutlineThickness(1);
	fuelBar.setPosition(150, 515);
	fuelBar.setFillColor(FUEL_COLOR);

	//set up the engine sound
	if (!playerBuffer.loadFromFile("ASSETS\\Sounds\\engine.wav"))
	{
		std::cout << "player sound not loaded" << std::endl;
	}
	engineSound.setBuffer(playerBuffer);
	engineSound.setVolume(10);
	engineSound.setLoop(true);

	//set up the shield sound
	if (!shieldBuffer.loadFromFile("ASSETS\\Sounds\\shield.wav"))
	{
		std::cout << "shield not loaded" << std::endl;
	}
	shieldSound.setBuffer(shieldBuffer);
	shieldSound.setVolume(10);
}

/// <summary>
/// default destructor
/// </summary>
Player::~Player()
{
}

/// <summary>
/// update player variables
/// </summary>
void Player::update()
{
	
	//decrement the safety timer
	if (safetyTimer > 0)
	{
		safetyTimer--;
	}
	shielPos = position;//set the shield position to be the same as the player position
	fuelBar.setSize(sf::Vector2f(fuel, 30));//reset the fuel bar size to be the length of the amoutn of fuel you have

	//if the fuel is lower than 30 set the fuel bar colour to be red
	if (fuel <= 30)
	{
		fuelBar.setFillColor(sf::Color::Red);
	}

	checkRotate();//check if the user presses a rotate key
	move();//update the player position and check for movement input

	armourCheck();//check if the player is using the armour
	bulletCheck();//check if the bullet is shot and update any bullet variables
	playSounds();
}

/// <summary>
/// render the player shield and bullets
/// </summary>
void Player::render()
{
	//loop throughh all of the bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		//if the bullet is alive draw it
		if (bullets[i].isActive)
		{
			Game::m_window.draw(bullets[i].body);
		}
	}
	//if the player is alive draw it
	if (isAlive)
	{
		Game::m_window.draw(body);
	}
	//if the players armour is alive draw it
	if (armourActive)
	{
		Game::m_window.draw(shieldbody);
	}
}

/// <summary>
/// reset the players variable sat the start of a new level
/// </summary>
void Player::reset()
{
	safetyTimer = 120;//reset the safety timer to be 120
	isAlive = true;//set the player to be alive
	
	position = originalPosition;//reset the position
	body.setPosition(position);//set the position of the player

	shielPos = position;//reset the shield position
	shieldbody.setPosition(shielPos);//set the position of the shield body

	velocity = {0,0,0};//reset the velocity
	bearing = originalBearing;//reset the bearing
	body.setRotation(0);//reset the rotation
	
	fuel = originalFuel;//reset the fuel
	armour = originalArmour;//reset the armour
	counter = 0;//reset the counter
	fuelBar.setFillColor(FUEL_COLOR);//change th fuel colour

	//reset all of the bullets to be false
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i].isActive = false;
		bullets[i].timer = 0;
	}
}

/// <summary>
/// update the player position and take user movement input
/// </summary>
void Player::move()
{
	//if w is pressed and the fuel isnt empty
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (fuel != 0)
		{
			fuel--;//decrement the fuel
			velocity += bearing;//add the bearing onto the velocity to increase the speed of the ship
		}
	}
	

	//if s is pressed slow down the players velocity and play the ship noise
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity = velocity * (float)0.96;
	}
	
	//if the length of the velocity vector is less than 0.1 then  reset the velocity to 0
	if (velocity.length() < 0.01f)
	{
		velocity = { 0,0,0 };
	}
	else//otherwise apply space friction
	{
		velocity = velocity * 0.99f;
	}

	//add the velocity onto the position
	position += velocity;
	//check screen wrapping
	//left
	if (position.X() < (0 - 2 * radius))
	{
		position = { (double)800 + radius, position.Y(),0 };
	}
	//right
	else if (position.X() >= (800 + radius))
	{
		position = { (double)(0 - 2 * radius), position.Y(),0 };
	}
	//top
	if (position.Y() <= 0 - 2 * radius)
	{
		position = { position.X(),(double)600 + radius,0 };
	}
	//bottom
	else if (position.Y() >= 600 + 2 * radius)
	{
		position = { position.X(), (double)(0 - 2 * radius),0 };
	}
	//set the shield position
	shielPos = position;
	shieldbody.setPosition(shielPos);
	//set the body position
	body.setPosition(position);

	//if the S or W key is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) && fuel > 0)
	{
		engineSoundActive = true; //set the engine sound to play
	} 
	//if W or S is not pressed
	else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || fuel == 0)
	{
		if (engineSoundActive) //if the engine sound is playing
		{ 
			engineSoundActive = false; //set the engine sound to stop
		}
	}

	
}

/// <summary>
/// rotate the player
/// </summary>
/// <param name="angle">the angle the body is rotated</param>
void Player::rotate(float angle)
{
	//if the angle is greater than 0 add to the counter
	if (angle > 0)
	{
		bearing.m_x = bearing.X() * cos(0.0698132) - bearing.Y() * sin(0.0698132);
		bearing.m_y = bearing.X() * sin(0.0698132) + bearing.Y() * cos(0.0698132);
		counter++;
	}
	else//otherwise subtract form the counter
	{
		bearing.m_x = bearing.X() * cos(-0.0698132) - bearing.Y() * sin(-0.0698132);
		bearing.m_y = bearing.X() * sin(-0.0698132) + bearing.Y() * cos(-0.0698132);
		counter--;
	}

	body.rotate(angle);//rotate the body

	//if the counter is greater than 120 or less than -120 reset the counter and the rotation and the bearing
	if (counter >= 90 || counter <= -90)
	{
		counter = 0;
		body.setRotation(0);
		bearing = originalBearing;
	}
}

/// <summary>
/// play the ship sounds
/// </summary>
void Player::playSounds()
{
	//if the engine sound playing bool is set to true
	if (engineSoundActive)
	{
		if (engineSound.getStatus() == !sf::SoundSource::Playing) //if the engine sound isn't playing
		{
			engineSound.play(); //play the engine sound
		}

	}
	else if (!engineSoundActive) // if engine sound is not active
	{
		engineSound.stop();//stop playing the engine sound
	}

	//if the shield sound is active play the shield sound
	if (shieldSoundActive)
	{
		if (shieldSound.getStatus() == !sf::SoundSource::Playing)//if shield sound isn't playing
		{
			shieldSound.play(); //play the shield sound
		}
	}
	else if (!shieldSoundActive) //if shield active is set to false
	{
		shieldSound.stop(); //stop playing the shield sound
	}
	
}

/// <summary>
/// check if the user iputs rotation input
/// </summary>
void Player::checkRotate()
{
	//if a is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//rotate counter clockwise
		rotate(-4);
		
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//rotate clockwise
		rotate(4);
		
		
	}
	
}

/// <summary>
/// check if the user shoots a bullet
/// </summary>
void Player::bulletCheck()
{
	//decrement the bullet timer
	if (bulletTimer > 0)
	{
		bulletTimer--;
	}

	//if space is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//if the bullet timer is 0
		if (bulletTimer == 0)
		{
			//loop through all bullets
			for (int i = 0; i < MAX_BULLETS; i++)
			{
				//if the bullet isnt active
				if (!bullets[i].isActive)
				{
					//play the bullet sound
					bullets[i].bulletShotSound.play();
					bullets[i].body.setRotation(0);//reset the rotation
					bullets[i].body.setRotation(body.getRotation());//set the rotation to be the same as the player body rotation
					//check roation problems
					if (bullets[i].body.getRotation() > 90 && bullets[i].body.getRotation() < 270)
					{
						bullets[i].position = { position.X() + 10, position.Y(), 0 };
					}
					else if (bullets[i].body.getRotation() < 90 || bullets[i].body.getRotation() > 270)
					{
						bullets[i].position = { position.X() - 10, position.Y() , 0 };
					}

					//set te bullet bearing
					bullets[i].bearing = bearing.unit() / bulletSpeed;
					bullets[i].position = bullets[i].position + (bullets[i].bearing * 200);//set the bullet position
					bullets[i].bearing = bullets[i].bearing * 65;//set the bearing again
					bullets[i].isActive = true;//set the bullet to be true
					bulletTimer = 45;//reset the bullet timer
					break;//break out of the loop
				}
			}
		}
	}
}

/// <summary>
/// check user armour input
/// </summary>
void Player::armourCheck()
{
	//if left control is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		//if the armour isnt 0
		if (armour != 0)
		{
			if (!shieldSoundActive)
			{
				shieldSoundActive = true;
			}
						
			armourActive = true;//set the armour active to be true
			armour--;//decrement the armour
		}
		else 
		{
			armourActive = false;//setthe armour to be false
		}
	}
	 if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		shieldSoundActive = false;
		armourActive = false;//set the armour to be false
	}
}