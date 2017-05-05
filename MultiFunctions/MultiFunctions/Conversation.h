#pragma once

#include "Asteroid.h"
#include "SpaceShip.h"
#include "SpaceStantion.h"

class Ñonversation
{
public:

	void Talk(Asteroid asteroid, SpaceShip ship);

	void Talk(Asteroid asteroid, SpaceStation station);

	void Talk(SpaceShip ship, SpaceStation station);
};