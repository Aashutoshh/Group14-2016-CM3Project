#include "Alien.h"
#include "BaseObject.h"
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

Alien::Alien()
{
}


Alien::~Alien()
{
}

void Alien::InitAlien(float x, float y, ALLEGRO_BITMAP *iimage, void(*TakeLife)(void))
{

}

void Alien::DestroyObject()
{
	BaseObject::DestroyObject();

}

void Alien::UpdateObject()
{
	BaseObject::UpdateObject();

}

void Alien::RenderObject()
{
	BaseObject::RenderObject();

}

void Alien::Collided(int objectType)
{

}