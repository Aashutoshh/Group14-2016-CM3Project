#pragma once
#include "BaseObject.h"
#include <string>

using namespace std;

class Asteroid : public BaseObject
{
private:
	void(*TakeLife)(void);

public:
	Asteroid();
	~Asteroid();

	Asteroid(float x, float y, ALLEGRO_BITMAP *iimage, void(*TakeLife)(void));

	//Overriding functions for base class virtual functions
	void DestroyObject();
	void UpdateObject();
	void RenderObject();
	void Collided(int objectID);
};

