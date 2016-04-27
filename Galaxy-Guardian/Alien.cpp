#include "Alien.h"
#include "BaseObject.h"
#include "Spaceship.h"
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

Alien::Alien()
{
}


Alien::~Alien()
{
}

void Alien::InitAlien(float ix, float iy, ALLEGRO_BITMAP *iimage, void(*TakeLife)(void))
{
	BaseObject::Init(ix, iy, 0.5, 0, -1, 0, 55, 35);  //Set it to stationery
	setObjType(ALIEN);

	maxFrame = 3;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 8;   //Delay of close to 10 fools the human into seeing motion in animation
	frameWidth = 106;
	frameHeight = 41;
	animationColumns = 3;

	image = iimage;
	Alien::TakeLife = TakeLife;
}

void Alien::DestroyObject()
{
	BaseObject::DestroyObject();

}

void Alien::UpdateObject()
{
	BaseObject::UpdateObject();

	if (++frameCount >= frameDelay)
	{
		if (++curFrame >= maxFrame)
			curFrame = 0;

		frameCount = 0;
	}

	if (x + frameWidth < 0)
		Collided(BORDER);
}

void Alien::RenderObject()
{
	BaseObject::RenderObject();

	int fx = curFrame*frameWidth;   //For simple one row sprite sheets
	int fy = 0;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight,
		x - frameWidth / 2, y - frameHeight / 2, 0);
}

void Alien::Collided(int iObjectType)
{
	if (iObjectType == BORDER)
	{
		x = 800;     //If they reach the border start back again
	}

	if (iObjectType == PLAYER)
	{
		setOnScreen(false);
		//TakeLife();  //NB The spaceship class already takes care of this
	}

	if (iObjectType == BULLET)
	{
		setOnScreen(false);
	}
}