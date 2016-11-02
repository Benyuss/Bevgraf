#pragma once

#include "Point.h"

class Line {
public:

	Line(Point, Point);

	Point a;
	Point b;

private:
	//TODO
	double red;
	double green;
	double blue;
	double width;

};