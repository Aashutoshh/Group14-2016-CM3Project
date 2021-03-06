#pragma once

#include <string>
#include "Globals.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;
//Main base object class declarations 
//All sub classes inherit from this class
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

	int boundaryX, boundaryY; //boundary of area surrounding an object --> used for collission detection

//Attributes for animation and rendering 

	int maxFrame;   //Maximum amount of frames in a row of a spritesheet
	int curFrame;   //Current frame in a row of a sprite sheet
	int frameCount; //frame count to help set FPS in game
	int frameDelay; 
	int frameWidth; //Width of sprite image from an index in the sprite sheet
	int frameHeight; //Height of sprite image from an index in the sprite sheet
	int animationColumns; //Number of columns in the sprite sheet
	int animationDirection; //Direction in move the animation updates

	// declaring the bitmap image pointer for using the bitmaps 
	ALLEGRO_BITMAP *image;

public:
	BaseObject();
	~BaseObject();

	//Can initialize any sub class object common attbs with this initializer method
	void Init(float ix, float iy, float speedX, float speedY, int idirectX, int idirectY, int iboundaryX, int iboundaryY); // initialization of any object method
	

	/********************************VIRTUAL FUNCTIONS TO BE OVERRIDED BY SUB CLASSES*********************/
	void virtual DestroyObject(); //Meant to do what a destructor does but instead this is a virtual function that
	                              //uses inheritance i.e it can be overriden when subclasses make the same call to release
	                              //resources allocated to that particular object of any sub class. It some cases this is
	                              //the better option instead of using a default destructor from the base class
	                              // methods for animation and rendering
	void virtual UpdateObject();  //Virtual functions using inheritance--Gives sub classes opportunity to use them and
	void virtual RenderObject();  //override them accordingly
	void virtual Collided(int iobjType); //After we determine that we collided with something, we can call this function to determine exactly what TYPE of
	//of object we collided with.

	//Accessor and Mutator with definition
	float getX(){ return x;  }
	float getY(){ return y; }

	int getBoundaryX(){ return boundaryX;  }
	int getBoundaryY(){ return boundaryY; }


	void setX(int ix){ x = ix; }
	void setY(int iy){ y = iy; }
	void setspeedX(int ispeedX){ speedX = ispeedX; } //set horizontal speed
	void setspeedY(int ispeedY){ speedY = ispeedY; }
	void setdirectX(int idirectX){ directX = idirectX; }
	void setdirectY(int idirectY){ directY = idirectY; }
	void setImage(ALLEGRO_BITMAP *iimage){ image = iimage; }

	void setObjType(int iobjType){ objType = iobjType; } 
	int getObjType(){ return objType; }

	bool getOnScreen(){ return onScreen; }
	void setOnScreen(bool ionScreen){ onScreen = ionScreen; }

	bool getCheckCollision(){ return checkCollision; }
	void setCheckCollision(bool icheckCollision){ checkCollision = icheckCollision; }

	bool getCollision(BaseObject *otherObject);// checks if current object collided with input object
	                                           //Used to see if object crashed into another object using polymorphism
	                                           
	bool onScreenCollide(); //Combines the onScreen() and checkCollission() methods to only output a true value
	                       //only if an object is both onscreen and is collidable 
};



