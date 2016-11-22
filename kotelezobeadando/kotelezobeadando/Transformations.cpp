#include "Transformations.h"

void matrixMultiplication(double a[][3], double b[][3], double c[][3]) {
	int i, j, k;
	double sum;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) {
			sum = 0;
			for (k = 0; k < 3; k++)
				sum = sum + a[i][k] * b[k][j];
			c[i][j] = sum;
		}
}

HomogenPoint transform(double m[][3], HomogenPoint p)
{
	HomogenPoint q;
	q.x1 = m[0][0] * p.x1 + m[0][1] * p.x2 + m[0][2] * p.x3;
	q.x2 = m[1][0] * p.x1 + m[1][1] * p.x2 + m[1][2] * p.x3;
	q.x3 = m[2][0] * p.x1 + m[2][1] * p.x2 + m[2][2] * p.x3;
	return q;
}