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

// Update the object
void Bulllet::UpdateObject(){

	BaseObject::UpdateObject();

	if (x > width)
		Collided(BORDER);
}

//Render the object 
void Bulllet::RenderObject(){

	//The bullet  formed is simply a white primitive circle
	al_draw_filled_circle(x, y, 2, al_map_rgb(255, 255, 255));
}


// check whether a collision occurred if certain conditions are met
void Bulllet::Collided(int objectID)
{
	if (objectID == ENEMY || objectID == BORDER)
		setOnScreen(false);

	if (objectID == ENEMY)
		ScorePoint();
}