#include "Spaceship.h"
#include "BaseObject.h"


Spaceship::Spaceship()
{
}


Spaceship::~Spaceship()
{
}

void Spaceship::Init(ALLEGRO_BITMAP *imageIn) {
	
	BaseObject::Init(20, 200, 6, 6, 0, 0, 10, 15); //Call BaseObject Init to set the related protected attributes
												   // Original boundX = 10, boundY = 12
	setObjType(PLAYER);
	setOnScreen(true);  //Reinitialize the ship if you still have lives left

	lives = 3;
	score = 0;
	health = 100; //Start with 100 HP

	maxFrame = 3;       //NB These values are based on the sprite sheet for the spaceship --PM
	curFrame = 0;       //These will be different for other objects based on their own sprite sheet
	frameWidth = 46;
	frameHeight = 41;
	animationColumns = 3;
	animationDirection = 1;

	animationRow = 1;

	if (imageIn != NULL)
		Spaceship::image = imageIn;

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
	directY = -1;
}

void Spaceship::mvDOWN()
{
	animationRow = 2;
	directY = 1;
}

void Spaceship::mvLEFT()
{
	curFrame = 2;
	directX = -1;
}

void Spaceship::mvRIGHT()
{
	curFrame = 1;
	directX = 1;
}

void Spaceship::animationReset(int pos)
{
	if (pos == 1)
	{
		animationRow = 1;
		directY = 0;
	}
	else
	{
		curFrame = 0;
		directX = 0;
	}
}
