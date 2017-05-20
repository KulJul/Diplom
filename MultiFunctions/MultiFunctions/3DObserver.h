#pragma once

#include  "Observer.h"
#include "Triangle.h"
#include "Rectangle.h"

struct _3DObserver : Observer
{
	double camera_position_x;
	double camera_position_y;
	double camera_position_z;

	Triangle triangle;
	Rectangle rectangle;

	void Update()
	{

	}
};