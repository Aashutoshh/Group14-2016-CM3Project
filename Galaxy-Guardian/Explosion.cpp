#include "Explosion.h"
#include "BaseObject.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <ctime>

using namespace std;

Explosion::Explosion(float ix, float iy, ALLEGRO_BITMAP *iimage)
{
	BaseObject::Init(ix, iy, 0, 0, 0, 0, 0, 0);
	setObjType(EXPLOSION);
	setCheckCollision(false);  //not collidable

	maxFrame = 31;        //relative to sprite sheet
	curFrame = 0;
	frameCount = 0;
	frameDelay = 1;
	frameWidth = 128;
	frameHeight = 128;
	animationColumns = 8;
	animationDirection = 1;
	image = iimage;
}


Explosion::~Explosion()
{

}

void Explosion::DestroyObject()
{
	BaseObject::DestroyObject();
}

void Explosion::UpdateObject()
{
	BaseObject::UpdateObject();

	//NB NO BOUNDS CHECKING FOR Explosions

	if (++frameCount >= frameDelay)
	{
		curFrame += animationDirection;
		if (curFrame >= maxFrame)
		{
			setOnScreen(false);   //After the last frame remove explosion from screen
		}

		frameCount = 0;          //Reset Frame count for new explosion
	}

}

void Explosion::RenderObject()
{
	BaseObject::RenderObject(); //incase the method is updated 
	

	//Animation Updating
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;      //ingle row for animation therefore  not included here

	//Allegro drawing bitmap functions set up here for the space ship
	//NB must resolve in main.cpp to avoid unresolved symbols compilation error when building
	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}


void Explosion::Collided(int objectID)
{
	//We aren't concerned with what the explosion collides with so this is blank.
}