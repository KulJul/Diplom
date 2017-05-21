#pragma once

#ifndef SHAPE_H
#define SHAPE_H

//#include "Brush.h"
#include "ShapeMetricVisitor.h"
//#include "Observer.h"
//#include <vector>



struct Shape
{
	double position_x;
	double position_y;

	//Brush* brush;

	//virtual void Render()
	//{
	//	brush -> Draw();
	//}

	//virtual void Accept(ShapeMetricVisitor& metricVivsitor)
	//{}

	//Observer observers;

	//void Notify()
	//{
	//	
	//}

	virtual void foo()
	{

	}
};


#endif SHAPE_H