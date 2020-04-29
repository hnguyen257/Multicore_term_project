#include <iostream>
#include "determinant.h"
#include "gauss_jordan.h"

using namespace std;

double determinant(double const * const * input, int size)
{
	double** copy = new double* [size];
	for (int i = 0; i < size; i++)
	{
		copy[i] = new double[size];
	}
}
