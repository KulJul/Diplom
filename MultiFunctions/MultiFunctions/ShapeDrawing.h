#pragma once

#include "BoldBrush.h"
#include "ThinBrush.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "DinamicMultiMethod.h"

struct ShapeDrawing
{
	Loki::FnDispatcherLambda<Shape, Brush> dispatcher;

	void Init()
	{
		dispatcher.Add<Triangle, ThinBrush, true >([this](Triangle& shape, ThinBrush& brush)
		{
			return Drawing(shape, brush);
		});

		dispatcher.Add<Triangle, BoldBrush, true >([this](Triangle& shape, BoldBrush& brush)
		{
			return Drawing(shape, brush);
		});

		dispatcher.Add<Rectangle, ThinBrush, true >([this](Rectangle& shape, ThinBrush& brush)
		{
			return Drawing(shape, brush);
		});

		dispatcher.Add<Rectangle, BoldBrush, true >([this](Rectangle& shape, BoldBrush& brush)
		{
			return Drawing(shape, brush);
		});
	}

	void Drawing(Shape& shape, Brush& brush)
	{
		dispatcher.Go(shape, brush);
	}

	void Drawing(Triangle& shape, ThinBrush& brush)
	{
		
	}

	void Drawing(Triangle& shape, BoldBrush& brush)
	{
		
	}

	void Drawing(Rectangle& shape, ThinBrush& brush)
	{
		
	}

	void Drawing(Rectangle& shape, BoldBrush& brush)
	{
		
	}
};