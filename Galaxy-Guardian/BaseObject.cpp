#include <iostream>


#include "BaseObject.h"

/*Class Definitions for Methods, Constructors and Destructors Here!!*/
BaseObject::BaseObject()
{
	//Default Base class constructor. Due to inheritance each sub class object also attains their own instances
	//of these attributes wheneve they are created

	x = 0;  //Object position
	y = 0;

	speedX = 0;  //Object speed
	speedY = 0;

	directX = 0; //Object direction of movement
	directY = 0;

	boundaryX = 0; //boundaries of surrounding object's area
	boundaryY = 0;

	 maxFrame = 0;  //Necessary animation allegro attributes for animating an object
	 curFrame= 0;
	 frameCount=0;
	 frameDelay=0;
	 frameWidth=0;
	 frameHeight=0;
	 animationColumns=0;
	 animationDirection=0;

	 image = NULL;
	onScreen = true;
	checkCollision = true;

}


BaseObject::~BaseObject()
{
	//Default Base Class blank Destructor
}

void BaseObject::DestroyObject()
{
	//Similar to a blank destructor except this can be overridden by sub class objects
	//to release their own associated resources. Demos inheritance and polymorphism
}

void BaseObject::Init(float ix, float iy, float ispeedX, float ispeedY, int idirectX, int idirectY, int iboundaryX, int iboundaryY){

	// performs generic setup of the common variables used in the program by all objects
	x = ix;
	y = iy;

	speedX = ispeedX;
	speedY = ispeedY;

	directX = idirectX;
	directY = idirectY;

	boundaryX = iboundaryX;
	boundaryY = iboundaryY;

}

//Methods for updating object position and rendering

void BaseObject::UpdateObject(){

	//Every object will update in a similar manner depending on its x,y position and
	//speedx, speedy values.
	//If an object is meant to be stationery we just set its speed to 0 stopping its updation any further

	x += speedX*directX;
	y += speedY*directY;
}

void BaseObject::RenderObject(){
	//This only exists in base class to be made virtual so sub classes can override it with their own rendering
}

bool BaseObject::getCollision(BaseObject *otherObject)
{
	//Get the x,y position of the incoming input object in temp variables
	float otherX = otherObject->getX();
	float otherY = otherObject->getY();

	//Get the boundaries surrounding the incoming object in temp variables
	float oboundX = otherObject->getX();
	float oboundY = otherObject->getY();

	//Check for collision conditions between the 2 objects
	//Collision checking algortihm based on object centers and boundaries
	if (x + boundaryX > otherX - oboundX &&
		x - boundaryX < otherX + oboundX &&
		y + boundaryY > otherY - oboundY &&
		y - boundaryY < otherY + oboundY)

	{
		return true;
	}
	else
		return false;
}

void BaseObject::Collided(int iobjType){
	//Only exists to be virtual to give sub classes the ability to override it based on their objects collision status
}

bool BaseObject::onScreenCollide()
{
	//Will only return true if an object is BOTH alive and collidable
	//Otherwise it returns a false
	return onScreen && checkCollision;
}
	



