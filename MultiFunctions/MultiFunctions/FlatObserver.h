#pragma once


#include  "Observer.h"
#include "Triangle.h"
#include "Rectangle.h"

struct FlatObserver : Observer
{
	double scale_x;
	double scale_y;

	Triangle triangle;
	Rectangle rectangle;

	void Update()
	{

	}
};