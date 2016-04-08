#include "PowerUp.h"
#include "BaseObject.h"
#include <cstdio>
using namespace std;

PowerUp::PowerUp()
{

	
}

PowerUp::PowerUp(float xpos, float ypos, ALLEGRO_BITMAP *iimage)
{
	//initalizing object of type base
	BaseObject::Init(xpos, ypos, 5, 0, -1, 0, 35, 35);//initialize base object
	
	setObjType(POWER);//set type

	maxFrame = 2; //143;        //Change according to sprite sheet
	curFrame = 0;
	frameCount = 0;
	frameDelay = 10;  //2; 
	frameWidth = 64; //96;
	frameHeight = 57; //96;
	animationColumns = 2; //21;

	if (rand() % 2)        //Appear at random
		animationDirection = 1;
	else
		animationDirection = -1;

	image = iimage;
}

PowerUp::~PowerUp()
{
}
