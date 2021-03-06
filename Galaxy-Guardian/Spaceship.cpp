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

void Spaceship::DestroyObject()    //Overrides vf in base class
{
	BaseObject::DestroyObject();  //Call the base destroyer method
	//Get used to using scope res when calling methods from base class to avoid
	//confusion.
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

void Spaceship::UpdateObject()   //can override vf in base class
{
	BaseObject::UpdateObject(); //Call base class virtual function to get initial values for updating any object
	//This way we get the original values before using inheritance and polymorphism to override them
	//Now set the values according to what we want for our space ship
	if (x < 0)
		x = 0;
	else if (x > width)
		x = width;       //Keeps the space craft within horizontal bounds of the screen

	if (y < 0)
		y = 0;
	else if (y > height)
		y = height;    //Keeps the space craft within the vertical bounds of the screen
}

void Spaceship::RenderObject()
{
	BaseObject::RenderObject(); //Call base class virtual function just in case we update it later
	//Also gives us values that were initially set by base class vf before we may override them

	//Animation Updating
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRow * frameHeight;

	//Allegro drawing bitmap functions set up here for the space ship
	//NB must resolve in main.cpp to avoid unresolved symbols compilation error when building

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);

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
	if (iobjType == ALIEN || iobjType == ENEMY || iobjType == BOSS)
	{
		x = 20;  //If you collided with enemy reset player ship back to default position
		y = 560; //Spawn near bottom left of screen for safety
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