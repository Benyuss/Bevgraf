#pragma once

#include "Point.h"

/*
Circle class: 
P,d,d konstruktor -> be�ll�tja origo, radius, step (gyorsas�g)
destination -> az a Point, ahova az objektum tart(halad).
invertDestination -> viselked�s, amikor el�ri a "p�lya" sz�l�t. (visszapattan�s)
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