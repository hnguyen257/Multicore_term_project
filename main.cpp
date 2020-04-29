#include <iostream>
#include <omp.h>
#include "determinant.h"

using namespace std;

int main()
{
	omp_set_nested(true);

	double **test = new double* [4];
	test[0] = new double[5];
	test[1] = new double[5];
	test[2] = new double[5];
	test[3] = new double[5];
	test[0][0] = 1;
	test[0][1] = 2;
	test[0][2] = -3;
	test[0][3] = 3;
	test[0][4] = 5;
	test[1][0] = 4;
	test[1][1] = 10;
	test[1][2] = 6;
	test[1][3] = 3;
	test[1][4] = 1;
	test[2][0] = 7;
	test[2][1] = 81;
	test[2][2] = -9;
	test[2][3] = 3;
	test[2][4] = 6;
	test[3][0] = 1;
	test[3][1] = 22;
	test[3][2] = 3;
	test[3][3] = 3;
	test[3][4] = 9;
}
