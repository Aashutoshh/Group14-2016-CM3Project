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
	int objType;        //Integer value assigned to I.D the player, enemy or any other screen object
	bool onScreen;       //bool attribute to check if an object is still onscreen
	bool checkCollision; // collision status

protected :
	float x, y;            // position
	float speedX, speedY; // speed of object

	int directX, directY; //direction of movement 

	int boundaryX, boundaryY; //boundary of area surrounding an object

//Attributes for animation and rendering 

	int maxFrame;   //Maximum amount of frames in a row of a spritesheet
	int curFrame;   //Current frame in a row of a sprite sheet
	int frameCount; //frame count to help set FPS in game
	int frameDelay; 
	int frameWidth; //Width of sprite image from an index in the sprite sheet
	int frameHeight; //Height of sprite image from an index in the sprite sheet
	int animationColumns;
	int animationDirection;

	// declaring the bitmap image pointer for using the bitmaps 
	ALLEGRO_BITMAP *image;

public:
	BaseObject();
	~BaseObject();

	void virtual DestroyObject(); //Meant to do what a destructor does but instead this is a virtual function that
	                              //uses inheritance i.e it can be overriden when subclasses make the same call to release
	                              //resources allocated to that particular object of any sub class. It some cases this is
	                              //the better option instead of using a default destructor from the base class

	void init(float,float,float,float,int,int,int,int); // initialization of any object method

	// methods for animation and rendering
	void virtual UpdateObject();  //Virtual functions using inheritance--Gives sub classes opportunity to use them and
	void virtual RenderObject();  //override them accordingly


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

	bool getCollision(BaseObject *otherObject);// checks if current object collided with input object

	void virtual collided(int iobjType); //Check if current object collided with another
	
	bool onScreenCollide(); //Combines the onScreen() and checkCollission() methods to only output a true value
	                       //only if an object is both onscreen and is collidable 

};

#endif

