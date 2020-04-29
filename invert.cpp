#include <iostream>
#include <string>
#include "determinant.h"
#include "gauss_jordan.h"
#include "invert.h"

using namespace std;

double** invert(double const* const* input, int size)
{
	if (determinant(input, size) == 0)
	{
		cout << "Error: matrices with determinants of 0 are not invertible." << endl;
		return NULL;
	}

	double** copy = new double* [size];
	#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		copy[i] = new double[size * 2];
		memcpy(copy[i], input[i], size * sizeof(double));
		#pragma omp parallel for
		for (int j = 0; j < size; j++)
		{
			if (j == i)
			{
				copy[i][j + size] = 1;
			}
			else
			{
				copy[i][j + size] = 0;
			}
		}
	}

	gauss_jordan(copy, size, size, size * 2);

	#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		double* temp = new double[size];
		memcpy(temp, copy[i] + size, size * sizeof(double));
		delete[] copy[i];
		copy[i] = temp;
	}

	return copy;
}
