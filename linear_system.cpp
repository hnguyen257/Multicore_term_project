#include <string>
#include "gauss_jordan.h"
#include "linear_system.h"

using namespace std;

double** linear_system(double const* const* input, int equations, int variables)
{
	double** copy = new double* [equations];
	#pragma omp parallel for
	for (int i = 0; i < equations; i++)
	{
		copy[i] = new double[variables + 1];
		memcpy(copy[i], input[i], (variables + 1) * sizeof(double));
	}

	gauss_jordan(copy, equations, variables, variables + 1);

	return copy;
}
