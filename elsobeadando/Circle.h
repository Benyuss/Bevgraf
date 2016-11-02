#pragma once

#include "Point.h"

/*
Circle class: 
P,d,d konstruktor -> beállítja origo, radius, step (gyorsaság)
destination -> az a Point, ahova az objektum tart(halad).
invertDestination -> viselkedés, amikor eléri a "pálya" szélét. (visszapattanás)
*/
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