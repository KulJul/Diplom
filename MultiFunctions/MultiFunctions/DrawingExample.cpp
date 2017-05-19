#include  "Brush.h";
#include "Shape.h";
#include "BoldBrush.h";
#include "ThinBrush.h";
#include "Triangle.h";
#include  "Rectangle.h";


void DrawingExample()
{
	//логика находится внутри классов
	auto brush = new BoldBrush();

	auto shape = new Triangle();
	//shape->brush = brush;
	//
	//brush->Draw();


}