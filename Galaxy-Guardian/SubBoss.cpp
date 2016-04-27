#include "SubBoss.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>

using namespace std;

SubBoss::SubBoss()
{
}


SubBoss::~SubBoss()
{
}

SubBoss::SubBoss(float ix, float iy, ALLEGRO_BITMAP *iimage, void(*TakeLife)(void), void(*enemiesDown)(void), void(*bossesKilled)(void))
{
	BaseObject::Init(ix, iy, 5, 0, -1, 0, 55, 75);  // Default bounds 55,35
	setObjType(BOSS);
	subBossHP = 3;

	maxFrame = 3;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 8;   //Delay of close to 10 fools the human into seeing motion in animation
	frameWidth = 142;
	frameHeight = 121;
	animationColumns = 3;

	image = iimage;
	SubBoss::TakeLife = TakeLife;
	SubBoss::enemiesDown = enemiesDown;
	SubBoss::bossesKilled = bossesKilled;
}

void SubBoss::DestroyObject()
{
	BaseObject::DestroyObject();
}

void SubBoss::UpdateObject()
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

void SubBoss::RenderObject()
{
	BaseObject::RenderObject();

	int fx = curFrame*frameWidth;   //For simple one row sprite sheets
	int fy = 0;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight,
		x - frameWidth / 2, y - frameHeight / 2, 0);
}

void SubBoss::Collided(int objectID)
{
	if (objectID == PLAYER)
	{
		TakeLife();
		subBossHP = 0;
		setOnScreen(false);
	}

	if (objectID == BORDER)
	{
		subBossHP = 0;
		setOnScreen(false);
	}

	if (objectID == BULLET)
	{
		if (subBossHP > 0)
		{
			subBossHP--;    //Since default HP is 3 it will take three bullets to kill him
		}
		else
		{
			setOnScreen(false);
			bossesKilled();
		}
	}
}
