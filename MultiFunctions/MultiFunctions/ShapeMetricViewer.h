#pragma once

#include "Brush.h"
#include "ShapeMetricVisitor.h"
#include "Observer.h"
#include "Shape.h"
#include <vector>

#include "ShapeDrawing.h"
#include "MetricCounting.h"
#include "Observing.h"

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

	ShapeDrawing drawing;
	MetricCounting counting;
	Observing observing;
	ColorChanging colorChanging;

	Brush Brushes;
	ShapeMetricVisitor Metrics;
	Observer Observers;
	Shape Shapes;


	//void ReDrawingWithBrush(Brush* brush)
	//{
	//	//выбираем все фигуры связанные с этой кистью
	//	//for(Shape shape : Shapes)
	//	//{
	//	//	if(shape.brush == brush)
	//	//	{
	//	//		shape.Render();
	//	//		shape.Notify();
	//	//	}
	//	//}
	//}

	//void RecalculateMetricsAndRedraw(Shape* shape)
	//{
	//	//for (ShapeMetricVisitor metric : Metrics)
	//	//{
	//	//	shape->Accept(metric);
	//	//	shape->Notify();
	//	//}
	//}






};


struct SimpleShapeMetricDirector : ShapeMetricDirector
{

};


struct ShapeMetricDirectorWithVerification :ShapeMetricDirector
{

};
