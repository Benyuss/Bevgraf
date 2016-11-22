#pragma once

class Point {
public:

	Point();

	Point(double x, double y) : xCord(x), yCord(y) {
		//inicializációs lista, konstruktor törzse előtt fut
	}

	double xCord;
	double yCord;
};