#ifndef _MML_EXAMPLE_GAME_HIERARCHY_HPP_INCLUDED_
#define _MML_EXAMPLE_GAME_HIERARCHY_HPP_INCLUDED_


struct game_object
{
	virtual ~game_object()
	{
	}
};


struct space_ship
	: public game_object
{
};

struct space_station
	: public  game_object
{
};

struct asteroid
	: public game_object
{
};

#endif 