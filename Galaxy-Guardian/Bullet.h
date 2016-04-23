#pragma once
#include "BaseObject.h"
#include <string>
using namespace std;




//Declaration for spaceship bullet class
// Polymorphism displayed 
class Bullet :  public BaseObject{
	 
private:
	void(*enemiesDown)(void);
	void(*bossesKilled)(void);

public:
	Bullet(float x, float y, void(*enemiesDown)(void), void(*bossesKilled)(void), ALLEGRO_BITMAP *iimage);
	~Bullet();


	//Functions to override base class Virtual Functions
	void DestroyObject();
	void UpdateObject();
	void RenderObject();
	void Collided(int objectID);


};

