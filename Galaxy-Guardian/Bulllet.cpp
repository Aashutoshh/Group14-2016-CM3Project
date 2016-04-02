#include "Bulllet.h"
#include "BaseObject.h"


// Bullet Class methods 

//  Default constructor
Bulllet::Bulllet(){
}

//Default destructor
Bulllet::~Bulllet(){
}


Bulllet::Bulllet(float x, float y, void(*ScorePoint)(void)){
	BaseObject::Init(x, y, 10, 0, 1, 0, 0, 0);

	setObjType(BULLET);

	Bulllet::ScorePoint = ScorePoint;
}

// Destroy the object 
void Bulllet::DestroyObject(){

	BaseObject::DestroyObject();
}

// Update to check whether a collision occurred 
void Bulllet::UpdateObject(){

BaseObject::UpdateObject();

	if (x > width)
		Collided(BORDER);
}

