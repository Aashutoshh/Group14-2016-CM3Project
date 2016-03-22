#include <iostream>


#include "BaseObject.h"

/*Class Definitions for Methods, Constructors and Destructors Here!!*/
BaseObject::BaseObject()
{
	x = 0;
	y = 0;
	speedX = 0;
	speedY = 0;
	directX = 0;
	directY = 0;
	boundaryX = 0;
	boundaryY = 0;

	 maxFrame = 0;
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
}
void BaseObject::init(float ix, float iy, float ispeedX, float ispeedY, int idirectX, int idirectY, int iboundaryX, int iboundaryY){

	// performs generic setup of the common variables used in the program
	x = ix;
	y = iy;

	speedX = ispeedX;
	speedY = ispeedY;

	directX = idirectX;
	directY = idirectY;

	boundaryX = iboundaryX;
	boundaryY = iboundaryY;


}

void BaseObject::collided(int iobjType){
	// exists to be virtual to give sub classes the ability to override it.
}
