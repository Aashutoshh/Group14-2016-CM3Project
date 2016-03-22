#pragma once
#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include <string>

using namespace std;
//Main base object class declarations
//All sub classes inherit from this class

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

//Declarations

class BaseObject{
private: 
	int objType;
	bool onScreen;
	bool checkCollision; // collision status

protected :
	float x, y; // position
	float speedX, speedY; // speed of object

	int directX, directY; //direction of movement 

	int boundaryX, boundaryY; //boundary condition
//Attributes for animation and rendering 

public:
	BaseObject();
	~BaseObject();
	void init(float,float,float,float,int,int,int,int); // initialization of any object method

	// methods for animation and rendering

	//Accessor and Mutator with definition
	float getX(){ return x;  }
	float getY(){ return y; }

	int getBoundaryX(){ return boundaryX;  }
	int getBoundaryY(){ return boundaryY; }


	void setX(int ix){ x = ix; }
	void setY(int iy){ y = iy; }

	void setObjType(int iobjType){ objType = iobjType; }
	int getObjType(){ return objType; }

	bool getOnScreen(){ return onScreen; }
	void setOnScreen(bool ionScreen){ onScreen = ionScreen; }

	bool getCheckCollision(){ return checkCollision; }
	void setCheckCollision(bool icheckCollision){ checkCollision = icheckCollision; }

	bool getCollision(){ BaseObject *otherObject; }// checks if current object collided with input object
	void virtual collided(int iobjType); // is called when collision takes place 






};

#endif

