#pragma once
#ifndef _MOUTH_H
#define _MOUTH_H
#include "HomogenPoint.h"

class Mouth {
public:

	Mouth() {};

	Mouth(HomogenPoint xp, HomogenPoint yp, HomogenPoint zp, HomogenPoint ggwp) : first(xp), second(yp), third(zp), fourth(ggwp) {};

	HomogenPoint first;
	HomogenPoint second;
	HomogenPoint third;
	HomogenPoint fourth;

	void draw();
};

#endif // !1