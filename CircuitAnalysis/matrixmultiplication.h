#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef matrixmultiplication.h
#define matrixmultiplication.h


struct matrix matrix_multiply(struct matrix matrix1, struct matrix matrix2)
{
	//Multiplies matrix1 by matrix2
	struct matrix matrix = {
	.A = {0},
	.B = {0},
	.C = {0},
	.D = {0},
	};

	matrix.A = matrix1.A * matrix2.A + matrix1.B * matrix2.C;
	matrix.B = matrix1.A * matrix2.B + matrix1.B * matrix2.D;
	matrix.C = matrix1.C * matrix2.A + matrix1.D * matrix2.C;
	matrix.D = matrix1.C * matrix2.B + matrix1.D * matrix2.D;

	return matrix;
}

#endif