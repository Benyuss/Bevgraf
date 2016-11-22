#pragma once
#ifndef _CHUNK_H
#define _CHUNK_H
#include "HomogenPoint.h"


class Chunk {
public:

	Chunk() {};

	Chunk(HomogenPoint fp, HomogenPoint sp, HomogenPoint tp) : first(fp), second(sp), third(tp) {};

	HomogenPoint first;
	HomogenPoint second;
	HomogenPoint third;

	void draw();
};

#endif // !_CHUNK_H