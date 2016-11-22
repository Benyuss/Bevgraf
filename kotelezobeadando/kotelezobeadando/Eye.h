#pragma once
#include "Point.h"

class Eye {
public: 

	Eye(Point firstPassed, Point secondPassed, Point thirdPassed) : first(firstPassed), second(secondPassed), third(thirdPassed) {};

	Point first;
	Point second;
	Point third;
};