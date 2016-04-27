#include "Bullet.h"
#include "BaseObject.h"
#include <string>

using namespace std;

Bullet::Bullet(float x, float y, void(*enemiesDown)(void), void(*bossesKilled)(void), ALLEGRO_BITMAP *iimage){

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

	BaseObject::DestroyObject();
}

void Bullet::UpdateObject(){

	BaseObject::UpdateObject();

	if (++frameCount >= frameDelay){

		if (++curFrame >= maxFrame)
			curFrame = 0;

		frameCount = 0;
	}

	if (x > width)
		Collided(BORDER);
}

void Bullet::RenderObject(){

	BaseObject::RenderObject();

	//al_draw_filled_circle(x, y, 2, al_map_rgb(255, 255, 255)); //Bullet is a simple white primitive circle
	al_draw_bitmap_region(image, curFrame * frameWidth, 0, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}

void Bullet::Collided(int objectID){

	if (objectID == ENEMY || objectID == BORDER || objectID == ALIEN || objectID == BOSS)
		setOnScreen(false);

	if (objectID == ENEMY || objectID == ALIEN)
		enemiesDown();
}


Bullet::~Bullet(){
}
