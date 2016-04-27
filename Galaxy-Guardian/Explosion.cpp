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