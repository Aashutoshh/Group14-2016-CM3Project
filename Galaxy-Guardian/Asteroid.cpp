#include "Asteroid.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <ctime>

using namespace std;

Asteroid::Asteroid()
{

}


Asteroid::~Asteroid()
{

}

Asteroid::Asteroid(float x, float y, ALLEGRO_BITMAP *iimage, void(*TakeLife)(void))
{
	BaseObject::Init(x, y, 6, 0, -1, 0, 40, 40);

	setObjType(ENEMY);

	maxFrame = 143;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 2;
	frameWidth = 96;
	frameHeight = 96;
	animationColumns = 21;

	if (rand() % 2)
		animationDirection = 1;
	else
		animationDirection = -1;

	image = iimage;

	Asteroid::TakeLife = TakeLife;
}

void Asteroid::DestroyObject()
{
	BaseObject::DestroyObject();
}

void Asteroid::UpdateObject()
{
	BaseObject::UpdateObject();

	if (++frameCount >= frameDelay)
	{
		curFrame += animationDirection;
		if (curFrame >= maxFrame)
			curFrame = 0;
		else if (curFrame <= 0)
			curFrame = maxFrame;

		frameCount = 0;
	}

	if (x + frameWidth < 0)
		Collided(BORDER);
}

void Asteroid::RenderObject()
{
	BaseObject::RenderObject();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight,
		x - frameWidth / 2, y - frameHeight / 2, 0);
}

void Asteroid::Collided(int objectID)
{
	if (objectID == PLAYER || objectID == BORDER || objectID == BULLET)
	{
		//TakeLife();         //Spaceship code takes care of this
		setOnScreen(false);
	}

	/*if (objectID == BORDER || objectID == BULLET)
	{
	setOnScreen(false);
	}*/
}
