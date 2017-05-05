#pragma once

#include "SpaceShip.h"
#include "SpaceStantion.h"
#include "Asteroid.h"

class Collide
{
public:

	void Colliding(Asteroid& asteroid, SpaceShip& ship);

	void Colliding(Asteroid asteroid, SpaceStation station);

	void Colliding(SpaceShip ship, SpaceStation station);
};