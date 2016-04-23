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
	BaseObject::Init(ix, iy, 10, 0, -1, 0, 15, 15);
	setObjType(ALIENBULLET);

	maxFrame = 4; //1
	curFrame = 0;
	frameCount = 0;
	frameDelay = 10;   //Delay of close to 10 fools the human into seeing motion in animation
	frameWidth = 50; //32
	frameHeight = 19; //32
	animationColumns = 4; //1

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
