#pragma once
#include <string>
#include "BaseObject.h"

using namespace std;

class SubBoss : public BaseObject
{
private:
	int subBossHP;
	void(*TakeLife)(void);
	void(*enemiesDown)(void);
	void(*bossesKilled)(void);
public:
	SubBoss();
	~SubBoss();
	SubBoss(float x, float y, ALLEGRO_BITMAP *iimage, void(*TakeLife)(void), void(*enemiesDown)(void), void(*bossesKilled)(void));

	//Overriding functions for base class virtual functions
	void DestroyObject();
	void UpdateObject();
	void RenderObject();
	void Collided(int objectID);
};

