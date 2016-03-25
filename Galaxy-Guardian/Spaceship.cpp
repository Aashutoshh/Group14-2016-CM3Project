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
	score = 0;

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

void Spaceship::animationReset(int pos)
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

int Spaceship::getScore()
{
	return score;
}

void Spaceship::loseTry()
{
	tries--;
}

void Spaceship::addScore()
{
	score++;   //Will have to modify this later to account for 
	           //a bigger score updation when destroying bosses or
	           //tougher enemies
}



//*********************************************************************************************************************//
//============Functions which override or add to the Virtual Functions of the Base Class============================//
//**************************************************************************************************************//

void Spaceship::UpdateObject()   //can override vf in base class
{
	BaseObject::UpdateObject(); //Call base class virtual function to get initial values for updating any object
	//This way we get the original values before using inheritance and polymorphism to override them

	//Recall that every object updates in the same manner. So by using inheritance we call the base class
	//update method to see the current position and speed of our spaceship. After that we update the space ship
	//accordingly to its unique characteristics. Here we make sure that it doesn't go out of screen bounds during updation

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

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = animationRow * frameHeight;

	//Allegro drawing bitmap functions set up here for the space ship
	//NB must resolve in main.cpp to avoid unresolved symbols compilation error when building

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);

}

void Spaceship::DestroyObject()    //Overrides vf in base class
{
	BaseObject::DestroyObject();  //Call the base destroyer method
	//Get used to using scope res when calling methods from base class to avoid
	//confusion.
}

void Spaceship::Collided(int iobjType)
{
	if (iobjType == ENEMY)  //If we see we collided with an enemy craft then we lose a try
		tries--;
}