#pragma once

#include <string>
#include "BaseObject.h"

//Declaration for stage background class

class Background:public BaseObject
{
public:
	Background(ALLEGRO_BITMAP *iimage, float ispeedX);
	~Background();

	//Overriding functions for base class virtual functions
	void DestroyObject();
	void UpdateObject();
	void RenderObject();
};

