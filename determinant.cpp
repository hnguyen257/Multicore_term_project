#include <string>
#include "determinant.h"
#include "gauss_jordan.h"

using namespace std;

double determinant(double const * const * input, int size)
{
	double** copy = new double* [size];
	#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		copy[i] = new double[size];
		memcpy(copy[i], input[i], size * sizeof(double));
	}

	gauss(copy, size, size, size);

	double product = 1;
	#pragma omp parallel for reduction(*:product)
	for (int i = 0; i < size; i++)
	{
		product *= copy[i][i];
	}

	#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		delete[] copy[i];
	}
	delete[] copy;

	return product;
}
