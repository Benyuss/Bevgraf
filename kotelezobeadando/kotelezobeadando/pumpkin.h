#pragma once

#ifndef _PUMPKIN_H
#define _PUMPKIN_H
#include "Eye.h"
#include "Mouth.h"
#include "Tooth.h"
#include "Chunk.h"
#include <vector>
#include "HomogenPoint.h"
#include "Transformations.h"
#include <random>
#include <cmath>

#define PI 3.14159265359

const int windowWidth = 800;
const int windowHeight = 600;

class Pumpkin {
public:

	Pumpkin() {

		scale = randomGenerator(10, 100);
		alpha = randomGenerator(1, 360) * PI / 180;
		shiftX = randomGenerator(0, windowWidth - 2 * scale) + scale;
		shiftY = randomGenerator(0, windowHeight - 2 * scale) + scale;

		makeMatrixE();
		makeMatrixF();
		makeMatrixM();
		makeMatrixN();
		makeMatrixT();

		matrixMultiplication(scaling, rotate, trans);
		matrixMultiplication(mirror, trans, trans);
		matrixMultiplication(shift, trans, trans);

		A = initPt(HomogenPoint(0, 0.512));
		B = initPt(HomogenPoint(0.454, 0.565));
		C = initPt(HomogenPoint(0.815, 0.33));
		D = initPt(HomogenPoint(0.907, -0.313));
		E = initPt(HomogenPoint(0.411, -0.7));
		F = initPt(HomogenPoint(0, -0.7));
		G = initPt(HomogenPoint(-0.411, -0.7));
		H = initPt(HomogenPoint(-0.907, -0.313));
		I = initPt(HomogenPoint(-0.815, 0.33));
		J = initPt(HomogenPoint(-0.454, 0.565));

		K = initPt(HomogenPoint(-0.473, 0.045));
		L = initPt(HomogenPoint(-0.155, 0.028));
		M = initPt(HomogenPoint(-0.208, 0.32));

		N = initPt(HomogenPoint(0.196, 0.038));
		O = initPt(HomogenPoint(0.52, 0.055));
		P = initPt(HomogenPoint(0.312, 0.356));

		Q = initPt(HomogenPoint(-0.519, -0.226));
		R = initPt(HomogenPoint(0.59, -0.13));
		S = initPt(HomogenPoint(0.474, -0.505));
		T = initPt(HomogenPoint(-0.324, -0.524));

		E_1 = initPt(HomogenPoint(-0.202, -0.514));
		F_1 = initPt(HomogenPoint(-0.069, -0.518));
		G_1 = initPt(HomogenPoint(-0.069, -0.395));
		H_1 = initPt(HomogenPoint(-0.2, -0.4));

		U = initPt(HomogenPoint(0.358, -0.151));
		V = initPt(HomogenPoint(0.196, -0.165));
		W = initPt(HomogenPoint(0.216, -0.286));
		Z = initPt(HomogenPoint(0.374, -0.269));

		C_1 = initPt(HomogenPoint(-0.182, 0.681));
		D_1 = initPt(HomogenPoint(-0.063, 0.717));

		leftEye = Eye(K, L, M);
		rightEye = Eye(N, O, P);
		mouth = Mouth(Q, R, S, T);
		tooth1 = Tooth(V, W, Z, U);
		tooth2 = Tooth(F_1, G_1, H_1, E_1);
		chunk = Chunk(C_1, D_1, A);
	}

	Eye leftEye;
	Eye rightEye;
	Mouth mouth;
	Tooth tooth1;
	Tooth tooth2;
	Chunk chunk;

	//outline
	HomogenPoint A;
	HomogenPoint B;
	HomogenPoint C;
	HomogenPoint D;
	HomogenPoint E;
	HomogenPoint F;
	HomogenPoint G;
	HomogenPoint H;
	HomogenPoint I;
	HomogenPoint J;

	//eyeLeft
	HomogenPoint K;
	HomogenPoint L;
	HomogenPoint M;

	//eyeRight
	HomogenPoint N;
	HomogenPoint O;
	HomogenPoint P;

	//mouth
	HomogenPoint Q;
	HomogenPoint R;
	HomogenPoint S;
	HomogenPoint T;

	//Tooth1
	HomogenPoint E_1;
	HomogenPoint F_1;
	HomogenPoint G_1;
	HomogenPoint H_1;

	//Tooth2
	HomogenPoint U = HomogenPoint(0.358, -0.151);
	HomogenPoint V = HomogenPoint(0.196, -0.165);
	HomogenPoint W = HomogenPoint(0.216, -0.286);
	HomogenPoint Z = HomogenPoint(0.374, -0.269);

	//Chunk
	HomogenPoint C_1 = HomogenPoint(-0.182, 0.681);
	HomogenPoint D_1 = HomogenPoint(-0.063, 0.717);

	double scale;
	double shiftX;
	double shiftY;
	double alpha;

	double rotate[3][3];
	double shift[3][3];
	double mirror[3][3];
	double scaling[3][3];
	double trans[3][3];

	void makeMatrixM();
	void makeMatrixN();
	void makeMatrixF();
	void makeMatrixT();
	void makeMatrixE();

	void draw();

	double randomGenerator(double begin, double end);

	HomogenPoint initPt(HomogenPoint);

};

#endif // !_PUMPKIN_H