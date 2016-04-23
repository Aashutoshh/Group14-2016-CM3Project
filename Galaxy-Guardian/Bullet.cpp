#include "Bullet.h"
#include "BaseObject.h"
#include <string>

using namespace std;

Bullet::Bullet(float x, float y, void(*enemiesDown)(void), void(*bossesKilled)(void), ALLEGRO_BITMAP *iimage)
{
	BaseObject::Init(x, y, 10, 0, 1, 0, 0, 0);

	setObjType(BULLET);
	image = iimage;

	//Bullet Animation
	maxFrame = 5;  //Necessary animation allegro attributes for animating an object
	curFrame = 0;
	frameCount = 0;
	frameDelay = 8;
	frameWidth = 32;
	frameHeight = 21;

	Bullet::enemiesDown = enemiesDown;
	Bullet::bossesKilled = bossesKilled;
}


void Bullet::DestroyObject(){
	
}

void Bullet::UpdateObject(){
	
}

void Bullet::RenderObject(){

	

	
}

void Bullet::Collided(int objectID){
	
}

Bullet::~Bullet(){
}
