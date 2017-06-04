#pragma once

#include  "Shape.h"

struct  Triangle : Shape
{
	double angle;
	double base;
	double hight;

	//void Render()
	//{
	//	brush -> Draw();
	//}

	//void Accept(ShapeMetricVisitor& metricVivsitor)
	//{
	//	//metricVivsitor.VisitRectangle(this);
	//}

	void SizeWasChanged()
	{

	}
};