#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include "Brush.h"
#include "ShapeMetricVisitor.h"
//#include "Observer.h"
//#include <vector>

struct  Brush;

struct Shape
{
	double position_x;
	double position_y;

	ShapeMetricDirector director;

	//Brush* brush;

	//virtual void Render()
	//{
	//	brush -> Draw();
	//}

	//virtual void Accept(ShapeMetricVisitor& metricVivsitor)
	//{
	//
	//}

	//Observer observers;

	//void Notify()
	//{
	//	//оповещает обсервер об изменениях
	//}

	virtual void SizeWasChanged()
	{
		director.RecalculateMetricsAndRedraw(this);
	}




};


#endif SHAPE_H