#pragma once

#include "Brush.h"
#include "ShapeMetricVisitor.h"
#include "Observer.h"
#include "Shape.h"
#include <vector>

struct  Brush;
struct ShapeMetricVisitor;
struct  Observer;
struct Shape;

struct ShapeMetricDirector
{
	//std::vector<Brush> Brushes;
	//std::vector<ShapeMetricVisitor> Metrics;
	//std::vector<Observer> Observers;
	//std::vector<Shape> Shapes;

	Brush Brushes;
	ShapeMetricVisitor Metrics;
	Observer Observers;
	Shape Shapes;

	virtual void ReDrawingWithBrush(Brush* brush)
	{

	}

	virtual void RecalculateMetricsAndRedraw(Shape* shape)
	{

	}

};

struct SimpleShapeMetricDirector : ShapeMetricDirector
{

	void ReDrawingWithBrush(Brush* brush)
	{

	}

	void RecalculateMetricsAndRedraw(Shape* shape)
	{

	}

};


struct ShapeMetricDirectorWithVerification : ShapeMetricDirector
{

	void ReDrawingWithBrush(Brush* brush)
	{

	}

	void RecalculateMetricsAndRedraw(Shape* shape)
	{

	}

};



