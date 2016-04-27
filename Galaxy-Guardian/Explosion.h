#pragma once

#include <string>
#include "BaseObject.h"

using namespace std;

class Explosion : public BaseObject
{
private:

public:
	Explosion(float ix, float iy, ALLEGRO_BITMAP *iimage);
	~Explosion();
//virtual functions 
	void DestroyObject(); 

	void UpdateObject(); 

	void RenderObject(); 

	void Collided(int objectID); 
};

