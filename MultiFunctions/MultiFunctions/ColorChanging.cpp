#pragma once
#include "BoldBrush.h"
#include "ThinBrush.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "DinamicMultiMethod.h"
#include "ShapeMetricVisitor.h"

struct ColorChanging
{
	Loki::FnDispatcherLambda<ShapeMetricDirector, Brush> dispatcher;

	void Init()
	{
		//dispatcher.Add<Triangle, AreaVisitor, true >([this](Triangle& shape, AreaVisitor& metricCounter)
		//{
		//	return CountMetric(shape, metricCounter);
		//});

		//dispatcher.Add<Triangle, SumAngleVisitor, true >([this](Triangle& shape, SumAngleVisitor& metricCounter)
		//{
		//	return CountMetric(shape, metricCounter);
		//});

		//dispatcher.Add<Rectangle, AreaVisitor, true >([this](Rectangle& shape, AreaVisitor& metricCounter)
		//{
		//	return CountMetric(shape, metricCounter);
		//});

		//dispatcher.Add<Rectangle, SumAngleVisitor, true >([this](Rectangle& shape, SumAngleVisitor& metricCounter)
		//{
		//	return CountMetric(shape, metricCounter);
		//});
	}

	void ColorChange(ShapeMetricDirector& director, Brush& brush)
	{
		//dispatcher.Go(shape, metricCounter);
	}

	//void CountMetric(Triangle& shape, AreaVisitor& metricCounter)
	//{

	//}

	//void CountMetric(Triangle& shape, SumAngleVisitor& metricCounter)
	//{

	//}

	//void CountMetric(Rectangle& shape, AreaVisitor& metricCounter)
	//{

	//}

	//void CountMetric(Rectangle& shape, SumAngleVisitor& metricCounter)
	//{

	//}
};