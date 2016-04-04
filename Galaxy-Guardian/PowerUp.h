#pragma once
#include "BaseObject.h"

//Declaration for special items class --> power ups and health

class PowerUp
{
public:
	PowerUp();
	PowerUp(float X, float Y, ALLEGRO_BITMAP *iimage); //Overloading constructor
	~PowerUp();

	
	//functions inherateded from base class

	void DestroyObject(); //destroy object of type power up

	void UpdateObject();  //update object power up
	
	void RenderObject(); // render object of power up
	
	void Collided(int objectID);  //collision
};

