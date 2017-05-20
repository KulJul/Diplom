#pragma once
#include "BoldBrush.h"
#include "ThinBrush.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "DinamicMultiMethod.h"

struct ShapeDrawing
{
	Loki::FnDispatcherLambda<Shape, ShapeMetricVisitor> dispatcher;

	void Init()
	{
		dispatcher.Add<Triangle, AreaVisitor, true >([this](Triangle& shape, AreaVisitor& metricCounter)
		{
			return CountMetric(shape, metricCounter);
		});

		dispatcher.Add<Triangle, SumAngleVisitor, true >([this](Triangle& shape, SumAngleVisitor& metricCounter)
		{
			return CountMetric(shape, metricCounter);
		});

		dispatcher.Add<Rectangle, AreaVisitor, true >([this](Rectangle& shape, AreaVisitor& metricCounter)
		{
			return CountMetric(shape, metricCounter);
		});

		dispatcher.Add<Rectangle, SumAngleVisitor, true >([this](Rectangle& shape, SumAngleVisitor& metricCounter)
		{
			return CountMetric(shape, metricCounter);
		});
	}

	void CountMetric(Shape& shape, ShapeMetricVisitor& metricCounter)
	{
		dispatcher.Go(shape, metricCounter);
	}

	void CountMetric(Triangle& shape, AreaVisitor& metricCounter)
	{

	}

	void CountMetric(Triangle& shape, SumAngleVisitor& metricCounter)
	{

	}

	void CountMetric(Rectangle& shape, AreaVisitor& metricCounter)
	{

	}

	void CountMetric(Rectangle& shape, SumAngleVisitor& metricCounter)
	{

	}
};