#pragma once

#ifndef _EYE_H
#define _EYE_H
#include <GL\glut.h>
#include "HomogenPoint.h"

class Eye {
public: 

	Eye() {};

	Eye(HomogenPoint fp, HomogenPoint sp, HomogenPoint tp) : first(fp), second(sp), third(tp) {};

	HomogenPoint first;
	HomogenPoint second;
	HomogenPoint third;

	void draw();
};

#endif // !_EYE_H