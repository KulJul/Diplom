#pragma once

#include "Triangle.h"
#include "Rectangle.h"

struct ShapeMetricVisitor
{
	virtual void VisitTriangle(Triangle& shape)
	{
		
	}
	virtual void VisitRectangle(Rectangle& shape)
	{
		
	}
};

struct AreaVisitor : ShapeMetricVisitor
{
	void VisitTriangle(Triangle& shape)
	{
		
	}
	void VisitRectangle(Rectangle& shape)
	{
		
	}
};

struct SumAngleVisitor : ShapeMetricVisitor
{
	void VisitTriangle(Triangle& shape)
	{

	}
	void VisitRectangle(Rectangle& shape)
	{

	}
};