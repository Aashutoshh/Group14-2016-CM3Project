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

//destroy base object
void PowerUp::DestroyObject()
{
	BaseObject::DestroyObject();
}

void PowerUp::UpdateObject()
{
	BaseObject::UpdateObject();

	if (++frameCount >= frameDelay)
	{
		curFrame += animationDirection;
		if (curFrame >= maxFrame)
		{
			curFrame = 0;
		}
		else if (curFrame <= 0)
		{
			curFrame = maxFrame - 1;
		}
		frameCount = 0;
	}

	if (x + frameWidth < 0)
	{
		Collided(BORDER);
	}
}

void PowerUp::RenderObject()
{


	BaseObject::RenderObject(); 
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;      


	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}

void PowerUp::Collided(int iobjectType)
{
	if (iobjectType == PLAYER)
	{
		setOnScreen(false);    //If it collides with the player then it dissappears off screen
	}
}