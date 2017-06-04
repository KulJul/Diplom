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

	void ReDrawingWithBrush(Brush* brush)
	{
		//�������� ��� ������ ��������� � ���� ������
		//for(Shape shape : Shapes)
		//{
		//	if(shape.brush == brush)
		//	{
		//		shape.Render();
		//		shape.Notify();
		//	}
		//}
	}

	void RecalculateMetricsAndRedraw(Shape* shape)
	{
		//for (ShapeMetricVisitor metric : Metrics)
		//{
		//	shape->Accept(metric);
		//	shape->Notify();
		//}
	}



};
