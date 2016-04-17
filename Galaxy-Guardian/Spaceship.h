#pragma once

#include <string>
#include "BaseObject.h"

using namespace std;
//Declaration for the main player spaceship class
//This declares the attributes and methods for our player space craft in the game

class Spaceship : public BaseObject    //Inheriting from base class
{
private: 
	int tries, enemiesDestroyed, animationRow;  //Attributes unique to Spaceship
	int bossesDestroyed;
	int shipHealth;
	int pwrupsCollected;   //Number of power ups collected --> add it to score as they update score as well

public:
	Spaceship();
	~Spaceship();

	//NB THIS INIT FUNCTION IS NOT THE SAME AS THE BASE CLASS OBJECT INIT METHOD
	//This is only used to initialize the spaceship if the user passes an image to it
	//This way we don't have to keep creating and destroying the spaceship each time the game is played.
	//It merely loads the image which is set along with other initializer attbs.
	void Init(ALLEGRO_BITMAP *iimage = NULL); //initializer function to set up space craft

	//Functions which overload and override the base class virtual functions
	void DestroyObject();  //Overrides virtual function from the base class
	void UpdateObject();
	void RenderObject();
	void Collided(int iobjType);

	//Methods to move the space craft around the screen
	void mvUp();
	void mvDOWN();
	void mvLEFT();
	void mvRIGHT();

	void animationReset(int pos); //Resets the space ship animation at designated position
	                              //Useful when craft is destroyed by enemy

	int getTries();  //Accessors
	int getEnemiesDestroyed();
	int getBossesDestroyed();
	int getHealth();
	int getPwrup();

	void setTry(int iTry){ tries = iTry; }
	void addTry();  //Used to increased tries if enough power ups collected
	void loseTry(); //called when player character dies
	void loseHealth(); //called when player gets hit by enemy fire
	void bodyCount(); //Updates player score
	void bossesDown(); //adds up boss ships death toll
};
