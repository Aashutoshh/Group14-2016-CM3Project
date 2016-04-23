#include "AlienBullet.h"
#include "BaseObject.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

AlienBullet::AlienBullet(float ix, float iy, ALLEGRO_BITMAP *iimage, void(*TakeHealth)(void))
{
	BaseObject::Init(ix, iy, 10, 0, -1, 0, 0, 0);
	setObjType(ALIENBULLET);

	//Animation parameters. Frame count etc etc


	//Pass in the animation image
	image = iimage;
	AlienBullet::TakeHealth = TakeHealth;
}


AlienBullet::~AlienBullet()
{
}

void AlienBullet::DestroyObject()
{
	BaseObject::DestroyObject();
}

void AlienBullet::UpdateObject()
{
	BaseObject::UpdateObject();

	if (++frameCount >= frameDelay)
	{
		if (++curFrame >= maxFrame)
			curFrame = 0;

		frameCount = 0;
	}

	if (x < 0)
		Collided(BORDER);
}


void AlienBullet::RenderObject()
{
	BaseObject::RenderObject();

	//al_draw_filled_circle(x, y, 8, al_map_rgb(255, 170, 255)); //Bullet is a simple magenta primitive circle

	int fx = curFrame*frameWidth;   //For simple one row sprite sheets
	int fy = 0;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight,
		x - frameWidth / 2, y - frameHeight / 2, 0);
}


void AlienBullet::Collided(int objectID)
{
	if (objectID == PLAYER || objectID == BORDER)
		setOnScreen(false);

	if (objectID == PLAYER)
		TakeHealth();
}
