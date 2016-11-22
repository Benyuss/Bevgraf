#pragma once
#include "Point.h"
#include "Utility.h"

class Outline {
public:

	Outline(Point origop, Point Ap, Point Bp,
		Point Cp, Point Dp, Point Ep, Point Fp,
		Point Gp, Point Hp, Point Ip, Point Jp) {
			A(Ap), B(Bp), C(Cp), D(Dp), E(Ep), F(Fp), G(Gp), H(Hp), I(Ip), J(Jp) {
	}

	Point origo;

	Point A;
	Point B;
	Point C;
	Point D;
	Point E;
	Point F;
	Point G;
	Point H;
	Point I;
	Point J;

};