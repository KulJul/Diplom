#pragma once

#include "library\Loki\DinamicMultiMethod.h"
#include  "Object.h";


struct Collapsing
{
	Loki::FnDispatcherLambda<game_object, game_object> dispatcher;

	void Init()
	{
#pragma region

		dispatcher.Add<asteroid, space_ship>([this](asteroid& asteroid, space_ship& ship)
		{
			return this->Collapse(asteroid, ship);
		});

		dispatcher.Add<space_ship, asteroid>([this](space_ship& ship, asteroid& asteroid)
		{
			return this->Collapse(ship, asteroid);
		});


		dispatcher.Add<asteroid, space_station>([this](asteroid& asteroid, space_station& stantion)
		{
			return this->Collapse(asteroid, stantion);
		});

		dispatcher.Add<space_station, asteroid>([this](space_station& stantion, asteroid& asteroid)
		{
			return this->Collapse(stantion, asteroid);
		});


		dispatcher.Add<space_ship, space_station>([this](space_ship& ship, space_station& stantion)
		{
			return this->Collapse(ship, stantion);
		});

		dispatcher.Add<space_station, space_ship>([this](space_station& stantion, space_ship& ship)
		{
			return this->Collapse(stantion, ship);
		});


		dispatcher.Add<asteroid, asteroid>([this](asteroid& first_asteroid, asteroid& second_asteroid)
		{
			return this->Collapse(first_asteroid, second_asteroid);
		});


		dispatcher.Add<space_ship, space_ship>([this](space_ship& first_ship, space_ship& second_ship)
		{
			return this->Collapse(first_ship, second_ship);
		});


		dispatcher.Add<space_station, space_station>([this](space_station& first_stantion, space_station& second_stantion)
		{
			return this->Collapse(first_stantion, second_stantion);
		});

#pragma endregion
	}

	void Collapse(game_object& first_object, game_object& second_object)
	{
		dispatcher.Go(first_object, second_object);
	}

	void Collapse(asteroid& asteroid, space_ship& ship)
	{
		//delete asteroid;
		//delete ship;
	}

	void Collapse( space_ship& ship, asteroid& asteroid)
	{
		Collapse(asteroid, ship);
	}


	void Collapse(asteroid& asteroid, space_station& stantion)
	{
		//delete asteroid;
		StantionDamage(stantion, 10);
	}

	void Collapse(space_station& stantion, asteroid& asteroid)
	{
		Collapse(asteroid, stantion);
	}


	void Collapse(space_ship& ship, space_station& stantion)
	{
		//delete ship;
		StantionDamage(stantion, 5);
	}

	void Collapse(space_station& stantion, space_ship& ship)
	{
		Collapse(ship, stantion);
	}


	void Collapse(asteroid& first_asteroid, asteroid& second_asteroid)
	{
		//delete first_asteroid;
		//delete second_asteroid;
	}


	void Collapse(space_ship& first_ship, space_ship& second_ship)
	{
		//delete first_ship;
		//delete second_ship;
	}


	void Collapse(space_station& first_stantion, space_station& second_stantion)
	{
		int rebound_level = 3;

		int senter_x = (first_stantion.x + second_stantion.x) / 2;
		int senter_y = (first_stantion.y + second_stantion.y) / 2;
		int senter_z = (first_stantion.z + second_stantion.z) / 2;

		first_stantion.x = (first_stantion.x - senter_x) * rebound_level + first_stantion.x;
		second_stantion.x = (second_stantion.x - senter_x) * rebound_level + second_stantion.x;

		first_stantion.y = (first_stantion.y - senter_y) * rebound_level + first_stantion.y;
		second_stantion.y = (second_stantion.y - senter_y) * rebound_level + second_stantion.y;

		first_stantion.z = (first_stantion.z - senter_z) * rebound_level + first_stantion.z;
		second_stantion.z = (second_stantion.z - senter_z) * rebound_level + second_stantion.z;

		StantionDamage(first_stantion, 50);
		StantionDamage(second_stantion, 50);
	}

	void StantionDamage(space_station& stantion, int damage)
	{
		int rest_field = stantion.protective_field - damage;
		if (rest_field < 0)
		{
			stantion.protective_field = 0;
			stantion.health = stantion.health - (-rest_field);
			if (stantion.health <= 0)
				;
				//delete stantion;
		}
		else
		{
			stantion.protective_field = rest_field;
		}
	}

};
