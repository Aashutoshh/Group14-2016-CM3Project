#pragma once
#include "BaseObject.h"
#include <string>
using namespace std;


//Declaration for spaceship bullet class

class Bulllet : public BaseObject{

	// private variables 
private:
	void(*ScorePoint)(void);
	// public variables 
public:
	Bulllet();
	~Bulllet();
	Bulllet(float x, float y, void(*ScorePoint)(void));


	//Functions to override base class Virtual Functions
	void DestroyObject();
	void UpdateObject();
	void RenderObject();
	void Collided(int objectID);
};