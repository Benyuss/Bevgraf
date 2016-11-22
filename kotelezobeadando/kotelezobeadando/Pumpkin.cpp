#include "pumpkin.h"

void Pumpkin::draw() {
	glColor3d(1.0, 0.5, 0.0);
	glBegin(GL_POLYGON);

	glVertex2d(A.x1 / A.x3, A.x2 / A.x3);
	glVertex2d(B.x1 / B.x3, B.x2 / B.x3);
	glVertex2d(C.x1 / C.x3, C.x2 / C.x3);
	glVertex2d(D.x1 / D.x3, D.x2 / D.x3);
	glVertex2d(E.x1 / E.x3, E.x2 / E.x3);
	glVertex2d(F.x1 / F.x3, F.x2 / F.x3);
	glVertex2d(G.x1 / G.x3, G.x2 / G.x3);
	glVertex2d(H.x1 / H.x3, H.x2 / H.x3);
	glVertex2d(I.x1 / I.x3, I.x2 / I.x3);
	glVertex2d(J.x1 / J.x3, J.x2 / J.x3);

	glEnd();

	leftEye.draw();
	rightEye.draw();
	mouth.draw();
	tooth1.draw();
	tooth2.draw();
	chunk.draw();
}

/*
http://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
*/
double randomGenerator(double begin, double end) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(begin, end);
	return dis(gen);
}

void Pumpkin::makeMatrixM() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			transform[i][j] = 0;
		}
	}
}

void Pumpkin::makeMatrixN() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			scaling[i][j] = 0;
		}
	}

	scaling[0][0] = scale;
	scaling[1][1] = scale;
	scaling[2][2] = 1;
}

void Pumpkin::makeMatrixF() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rotate[i][j] = 0;
		}
	}

	rotate[0][0] = cos(alpha);
	rotate[0][1] = -sin(alpha);
	rotate[1][0] = sin(alpha);
	rotate[1][1] = cos(alpha);
	rotate[2][2] = 1;
}

void Pumpkin::makeMatrixT() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			shift[i][j] = 0;
		}
	}

	shift[0][0] = 1;
	shift[0][2] = shiftX;
	shift[1][1] = 1;
	shift[1][2] = shiftY;
	shift[2][2] = 1;
}

void Pumpkin::makeMatrixE() {

	int genValue = (int)randomGenerator(0, 2);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mirror[i][j] = 0;
		}
	}

	switch (genValue) {
	case 0: {
		mirror[0][0] = 1;
		mirror[1][1] = 1;
		mirror[2][2] = 1;
		break;
	}
	case 1: {
		mirror[0][0] = -1;
		mirror[1][1] = 1;
		mirror[2][2] = 1;
		break;
	}
	case 2: {
		mirror[0][0] = 1;
		mirror[1][1] = -1;
		mirror[2][2] = 1;
	}

	}
}
