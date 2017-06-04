#pragma once

#include "ShapeMetricViewer.h"


struct Brush
{
	double x;
	double y;

	ShapeMetricDirector director;


	virtual void Draw()
	{
		
	}


	virtual void ChangeColor(int newColor)
	{
		director.ReDrawingWithBrush(this);
	}
};
