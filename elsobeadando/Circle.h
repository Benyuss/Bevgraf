#pragma once

#include "Point.h"

class Circle {
public:

	Circle();

	Circle(Point, double, double);

	void invertDestination(char b);

	Point origo;
	double radius;

	Point destination;

private:
	
};