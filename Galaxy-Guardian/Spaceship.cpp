#include "Spaceship.h"
#include "BaseObject.h"
#include <iostream>
#include <cstdio>

using namespace std;

Spaceship::Spaceship()
{
	//Keep the constructor blank since we cannot initialize the spaceship like this before we render it 
	//with an image in the main code using the init method.
}

Spaceship::~Spaceship()
{
	//blank default destructor
}

void Spaceship::DestroyObject()
{
	BaseObject::DestroyObject();  //Call the base destroyer method
	                             //Get used to using scope res when calling methods from base class to avoid
	                            //confusion.
}

void init(ALLEGRO_BITMAP *image = NULL)
{

}




