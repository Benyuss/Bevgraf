#pragma once
#ifndef _HOMOGENPOINT_H
#define _HOMOGENPOINT_H

class HomogenPoint {
public:
	HomogenPoint() {};

	HomogenPoint(double x1p, double x2p) : x1(x1p), x2(x2p), x3(1) {};

	double x1;
	double x2;
	double x3;
};

#endif // !_HOMOGENPOINT_H