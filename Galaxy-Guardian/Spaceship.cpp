#include "Spaceship.h"
#include "BaseObject.h"
#include <iostream>
#include <cstdio>

using namespace std;

Spaceship::Spaceship()
{
	//Keep the constructor blank since we cannot initialize the spaceship like this before we render it 
	//with an image in the main code using the init method.
}

Spaceship::~Spaceship()
{
	//blank default destructor
}

void Spaceship::Init(ALLEGRO_BITMAP *iimage)
{
	//We use this to initialize the spaceship instead since we pass an image
	//NB May have been able to do this by using an overloading constructor instead
	//The spaceship Init is different from the GameObject Init

	BaseObject::Init(20, 200, 6, 6, 0, 0, 10, 12); //Call BaseObject Init to set the related protected attributes

	setObjType(PLAYER); 
	setOnScreen(true);  //Reinitialize the ship if you still have lives left

	tries = 3;
	enemiesDestroyed = 0;
	bossesDestroyed = 0;
	pwrupsCollected = 0;
	shipHealth = 100; //Start with 100 H

	maxFrame = 3;       //NB These values are based on the sprite sheet for the spaceship --PM
	curFrame = 0;       //These will be different for other objects based on their own sprite sheet
	frameWidth = 46;
	frameHeight = 41;
	animationColumns = 3;
	animationDirection = 1;

	animationRow = 1; //Start from animation row 1 of sprite sheet

	if (iimage != NULL)
		Spaceship::image = iimage;	
}


void Spaceship::mvUp()
{
	animationRow = 0;  //NB Based on the sprite sheet in soln folder for spacecraft -- PM
	directY = -1;     // up is considered a negative convention in allegro
}

void Spaceship::mvDOWN()
{
	animationRow = 2;
	directY = 1;    //as we go down the screen it is considered a positive direction
}

void Spaceship::mvLEFT()
{
	curFrame = 2;
	directX = -1; //left is regarded as a negative horizontal direction in allegro
}

void Spaceship::mvRIGHT()
{
	curFrame = 1;
	directX = 1;  //right is regarded as a positive horizontal direction in allegro
}

void Spaceship::animationReset(int pos) //Reset the ships animation if its stops moving
{
	if (pos == 1)
	{
		animationRow = 1;
		directY = 0;   //set back to a neutral position i.e the object isn't moving in any Y direction
	}
	else
	{
		curFrame = 0;
		directX = 0;  //set back to a neutral position i.e the object isn't moving in any X direction
	}
}

int Spaceship::getTries()
{
	return tries;
}

int Spaceship::getEnemiesDestroyed()
{
	return enemiesDestroyed;
}

int Spaceship::getBossesDestroyed()
{
	return bossesDestroyed;
}

int Spaceship::getHealth()
{
	return shipHealth;
}

int Spaceship::getPwrup()
{
	return pwrupsCollected;
}

void Spaceship::loseTry()
{
	tries--;                    //Can be called when player directly collides with an enemy
	if (tries <= 0)
	{
		tries = 0;
	}
}

void Spaceship::addTry()
{
	tries++;
}

void Spaceship::loseHealth()
{

	if (shipHealth <= 0 && tries >= 0)
	{
		tries--;
		shipHealth = 100;
	}
	else
	{
		shipHealth = shipHealth - 25;
	}

	if (tries <= 0)
	{
		tries = 0;
	}
}

void Spaceship::bodyCount()
{
	enemiesDestroyed++;   //Will have to modify this later to account for 
	//a bigger score updation when destroying bosses or
	//tougher enemies
}

void Spaceship::bossesDown()
{
	bossesDestroyed++;
}

void Spaceship::Collided(int iobjType)
{
	if (iobjType == ALIEN || iobjType == ENEMY)
	{
		x = 20;  //If you collided with enemy reset player ship back to default position
		y = 200;
		tries--;
		enemiesDestroyed++; //Player would have sacrificed a life to destroy just one ship
	}

	if (iobjType == POWER)      //If collided with a health object
	{
		pwrupsCollected++;
		if (shipHealth < 100)
		{
			shipHealth = shipHealth + 25;
		}

		if (shipHealth > 100)       //If enough health is collected increase tries
		{
			shipHealth = 100;
		}

		if (pwrupsCollected == 30 || pwrupsCollected == 60 || pwrupsCollected == 90)
		{
			tries++;
		}

	}
}