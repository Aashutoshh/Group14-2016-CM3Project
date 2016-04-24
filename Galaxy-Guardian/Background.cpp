#include "Background.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <ctime>

Background::Background(ALLEGRO_BITMAP *iimage, float ispeedX)
{
	BaseObject::Init(0, 0, ispeedX, 0, -1, 0, 0, 0);
	setObjType(MISC);
	setCheckCollision(false);  //You cannot collide with a backdrop image

	image = iimage;
	frameWidth = al_get_bitmap_width(image);
}


Background::~Background()
{
}

void Background::DestroyObject()
{
	BaseObject::DestroyObject();
}

void Background::UpdateObject()
{
	BaseObject::UpdateObject(); //Move the background for a scrolling background according to user speed
	if (x + frameWidth <= 0)
	{
		x = 0;
	}
}

void Background::RenderObject()
{
	BaseObject::RenderObject();
	al_draw_bitmap(image, x, y, 0); //Pass in the whole image

	//Allow for looping
	if (x + frameWidth < width)
	{
		al_draw_bitmap(image, x + frameWidth, y, 0);
	}
}
