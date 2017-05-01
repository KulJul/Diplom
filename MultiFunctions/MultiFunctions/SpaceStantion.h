#pragma once

#include  "GameObject.h"

struct SpaceStation
	: GameObject
{

	double deltaX;
	double deltaY;
	double deltaZ;

	~SpaceStation();
};