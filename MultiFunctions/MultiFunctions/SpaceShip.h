#pragma once


#include  "GameObject.h"

struct SpaceShip
	: GameObject
{
	double length;
	double crossSectional;

	~SpaceShip();
};