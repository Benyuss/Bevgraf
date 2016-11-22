#pragma once
#ifndef _TRANSFORMATIONS_H
#define _TRANSFORMATIONS_H
#include "HomogenPoint.h"

void matrixMultiplication(double a[][3], double b[][3], double c[][3]);

HomogenPoint transform(double a[][3], HomogenPoint point); 

#endif // !_TRANSFORMATIONS_H