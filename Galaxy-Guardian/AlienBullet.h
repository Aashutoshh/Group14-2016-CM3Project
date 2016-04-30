#pragma once
#include"BaseObject.h"
#include <string>

using namespace std;

class AlienBullet : public BaseObject
{
private:
	void(*TakeHealth)(void);  //Pointer to fully global function in main.cpp

public:
	AlienBullet(float ix, float iy, ALLEGRO_BITMAP *iimage, void(*TakeHealth)(void));
	~AlienBullet();

	//Functions to override base class Virtual Functions
	void DestroyObject();
	void UpdateObject();
	void RenderObject();
	void Collided(int objectID);
};

