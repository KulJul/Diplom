#pragma once
#ifndef SHAPE_METRIC_VISITOR_H
#define SHAPE_METRIC_VISITOR_H

//#include "Triangle.h"
//#include "Rectangle.h"


struct Rectangle;
struct Triangle;

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

#endif SHAPE_METRIC_VISITOR_H
