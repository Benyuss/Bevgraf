#pragma once

#include "Point.h"

class Line {
public:

	Line(Point aGiven, Point bGiven) : a(aGiven), b(bGiven) {
		//inicializ�ci�s lista
	}

	Point a;
	Point b;

private:
	//TODO
	double red;
	double green;
	double blue;
	double width;

};