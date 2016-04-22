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

	//Alien bullet specific updation


	//What happens when a bullet reaches the border
	if (x < 0)
		Collided(BORDER);
}

void AlienBullet::RenderObject()
{
	BaseObject::RenderObject();

	//Test with a simple circle before using animation
	al_draw_filled_circle(x, y, 8, al_map_rgb(255, 170, 255)); //Bullet is simply a white primitive circle

	//After testing primitive circle, replace it with rendering parameters for bullet sprite sheet
}


void AlienBullet::Collided(int objectID)
{
	if (objectID == PLAYER || objectID == BORDER)
		setOnScreen(false);

	if (objectID == PLAYER)
		TakeHealth();
}
