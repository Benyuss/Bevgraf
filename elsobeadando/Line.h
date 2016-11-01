#pragma once

#include "Point.h"

class Line {
public:

	Line(Point x, Point y) : a(x), b(y) {
		//inicializációs lista, konstruktor törzse elõtt fut, mint egy static blokk
	}

	Point a;
	Point b;

private:
	double red;
	double green;
	double blue;
	double width;

};