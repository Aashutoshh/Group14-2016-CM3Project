#pragma once
#include "BaseObject.h"

#include <string>

using namespace std;
//Class declaration for general enemy array

class Alien : public BaseObject  //Inheriting attributes of base class
{
private: int alienHP;                        //Alien health points--> is increased with difficulty
		 //Using Dynamic Memory Allocation for 2D ARRAY Using pointer method
		 Alien** alienGrid = new Alien*[6]; //Grid of Aliens 6 X 6
		 void(*TakeLife)(void);
		 float tempX, tempY;

public:
	Alien();
	~Alien();
	void InitAlien(float x, float y, ALLEGRO_BITMAP *iimage, void(*TakeLife)(void));

	void DestroyObject(); //virtual function
	void UpdateObject(); //virtual function
	void RenderObject(); //virtual function
	void Collided(int objectType); //virtual function
};

