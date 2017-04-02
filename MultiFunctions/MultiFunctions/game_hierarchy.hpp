#ifndef _GAME_HIERARCHY_HPP_INCLUDED_
#define _GAME_HIERARCHY_HPP_INCLUDED_


struct game_object
{


    virtual ~game_object()
    {
    }
};


struct space_ship
    : game_object
{

	~space_ship() {}
};

struct space_station
    : game_object
{
	~space_station() {}
};

struct asteroid
    : game_object
{
	~asteroid() {}
};

#endif 
