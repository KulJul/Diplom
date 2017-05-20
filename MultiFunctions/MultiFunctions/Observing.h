#pragma once

#include "BoldBrush.h"
#include "ThinBrush.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "DinamicMultiMethod.h"
#include "3DObserver.h"
#include  "FlatObserver.h"
#include  "Observer.h"
#include <vector>

struct Observing
{
	Loki::FnDispatcherLambda<Shape, Observer> dispatcher;

	//std::vector<>

	void Init()
	{
		dispatcher.Add<Triangle, _3DObserver, true >([this](Triangle& shape, _3DObserver& observer)
		{
			return Observe(shape, observer);
		});

		dispatcher.Add<Triangle, FlatObserver, true >([this](Triangle& shape, FlatObserver& observer)
		{
			return Observe(shape, observer);
		});

		dispatcher.Add<Rectangle, _3DObserver, true >([this](Rectangle& shape, _3DObserver& observer)
		{
			return Observe(shape, observer);
		});

		dispatcher.Add<Rectangle, FlatObserver, true >([this](Rectangle& shape, FlatObserver& observer)
		{
			return Observe(shape, observer);
		});
	}

	void Observe(Shape& shape, Observer& observer)
	{
		dispatcher.Go(shape, observer);
	}

	void Observe(Shape& shape)
	{
		
	}

	void Observe(Triangle& shape, _3DObserver& observer)
	{

	}

	void Observe(Triangle& shape, FlatObserver& observer)
	{

	}

	void Observe(Rectangle& shape, _3DObserver& metricCounter)
	{

	}

	void Observe(Rectangle& shape, FlatObserver& metricCounter)
	{

	}
};