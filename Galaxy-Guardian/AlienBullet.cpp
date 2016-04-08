#include "AlienBullet.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

AlienBullet::AlienBullet(float ix, float iy, void(*TakeHealth)(void))
{
	BaseObject::Init(ix, iy, 10, 0, -1, 0, 0, 0);
	setObjType(ALIENBULLET);
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

	if (x < 0)
		Collided(BORDER);
}

void AlienBullet::RenderObject()
{
	al_draw_filled_circle(x, y, 8, al_map_rgb(255, 170, 255)); //Bullet is simply a white primitive circle
}


void AlienBullet::Collided(int objectID)
{
	if (objectID == PLAYER || objectID == BORDER)
		setOnScreen(false);

	if (objectID == PLAYER)
		TakeHealth();
}
