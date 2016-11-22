#pragma once
#include "Outline.h"
#include "Eye.h"

class Pumpkin {
public:

	Pumpkin(Point origoPassed, Outline outLinePassed, Eye left, Eye right) : origo(origoPassed), outLine(outLinePassed, origo), eyeLeft(left, origo), eyeRight(right, origo) {};
	
	Point origo;

	Outline outLine;
	Eye eyeLeft;
	Eye eyeRight;

};