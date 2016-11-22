#pragma once
#ifndef _TOOTH_H
#define _TOOTH_H
#include "HomogenPoint.h"

class Tooth {
public:

	Tooth() {};

	Tooth(HomogenPoint xp, HomogenPoint yp, HomogenPoint zp, HomogenPoint ggwp) : first(xp), second(yp), third(zp), fourth(ggwp) {};

	HomogenPoint first;
	HomogenPoint second;
	HomogenPoint third;
	HomogenPoint fourth;

	void draw();
};

#endif // !_TOOTH_H