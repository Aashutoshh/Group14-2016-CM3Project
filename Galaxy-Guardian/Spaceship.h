#pragma once
#include <string>
#include "BaseObject.h"
//Declaration for the main player spaceship class

class Spaceship:public BaseObject
{
private:
	int animationRow;
	int lives, score, health;
public:
	Spaceship();
	~Spaceship();
	void Init(ALLEGRO_BITMAP *imageIn = NULL);

	void UpdateObject();
	void RenderObject();

	//Methods to move the space craft around the screen
	void mvUp();
	void mvDOWN();
	void mvLEFT();
	void mvRIGHT();

	void animationReset(int pos); //Resets the space ship animation at designated position
								  //Useful when craft is destroyed by enemy
};

