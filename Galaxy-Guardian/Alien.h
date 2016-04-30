#pragma once
#include "BaseObject.h"
#include <string>

using namespace std;

class Alien : public BaseObject  //Inheriting attributes of base class
{
private: int alienHP;                        //Alien health points--> can be increased with difficulty		                                   
		 void(*TakeLife)(void);              //Pointer to TakeLife function in main.cpp


public:
	Alien();
	~Alien();
	void InitAlien(float x, float y, ALLEGRO_BITMAP *iimage, void(*TakeLife)(void));

	void DestroyObject(); //vf
	void UpdateObject(); //vf
	void RenderObject(); //vf
	void Collided(int objectType); //vf
};


