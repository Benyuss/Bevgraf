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

class Pumpkin {
public:

	std::vector<HomogenPoint> points;

	Pumpkin() {
		leftEye = Eye(K, L, M);
		rightEye = Eye(N, O, P);
		mouth = Mouth(Q, R, S, T);
		tooth1 = Tooth(V, W, Z, U);
		tooth2 = Tooth(F_1, G_1, H_1, E_1);
		chunk = Chunk(C_1, D_1, A);

		scale = randomGenerator(10, 100);
		alpha = randomGenerator(1, 360) * PI / 180;
		shiftX = 1; //TODO
		shiftY = 1; //TODO
	}

	Eye leftEye;
	Eye rightEye;
	Mouth mouth;
	Tooth tooth1;
	Tooth tooth2;
	Chunk chunk;

	//outline
	HomogenPoint A = HomogenPoint(0, 0.512);
	HomogenPoint B = HomogenPoint(0.454, 0.565);
	HomogenPoint C = HomogenPoint(0.815, 0.33);
	HomogenPoint D = HomogenPoint(0.907, -0.313);
	HomogenPoint E = HomogenPoint(0.411, -0.7);
	HomogenPoint F = HomogenPoint(0, -0.7);
	HomogenPoint G = HomogenPoint(-0.411, -0.7);
	HomogenPoint H = HomogenPoint(-0.907, -0.313);
	HomogenPoint I = HomogenPoint(-0.815, 0.33);
	HomogenPoint J = HomogenPoint(-0.454, 0.565);

	//eyeLeft
	HomogenPoint K = HomogenPoint(-0.473, 0.045);
	HomogenPoint L = HomogenPoint(-0.155, 0.028);
	HomogenPoint M = HomogenPoint(-0.208, 0.32);

	//eyeRight
	HomogenPoint N = HomogenPoint(0.196, 0.038);
	HomogenPoint O = HomogenPoint(0.52, 0.055);
	HomogenPoint P = HomogenPoint(0.312, 0.356);

	//mouth
	HomogenPoint Q = HomogenPoint(-0.519, -0.226);
	HomogenPoint R = HomogenPoint(0.59, -0.13);
	HomogenPoint S = HomogenPoint(0.474, -0.505);
	HomogenPoint T = HomogenPoint(-0.324, -0.524);

	//Tooth1
	HomogenPoint E_1 = HomogenPoint(-0.202, -0.514);
	HomogenPoint F_1 = HomogenPoint(-0.069, -0.518);
	HomogenPoint G_1 = HomogenPoint(-0.069, -0.395);
	HomogenPoint H_1 = HomogenPoint(-0.2, -0.4);

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

	void draw();
	
	double rotate[3][3];
	double shift[3][3];
	double mirror[3][3];
	double scaling[3][3];
	double transform[3][3];

	void makeMatrixM();
	void makeMatrixN();
	void makeMatrixF();
	void makeMatrixT();
	void makeMatrixE();

	double randomGenerator(double begin, double end);
};

#endif // !_PUMPKIN_H