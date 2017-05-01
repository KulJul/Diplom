#pragma once

#include "GameObject.h"

struct Asteroid
	: GameObject
{
	double diameter;

	~Asteroid();
};