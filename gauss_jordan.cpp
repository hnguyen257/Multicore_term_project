#include "gauss_jordan.h"

void gauss_jordan(double** input, int m, int n, int aug_n)
{
	gauss(input, m, n, aug_n);
	jordan(input, m, n, aug_n);
}

void gauss(double** input, int m, int n, int aug_n)
{
	for (int i = 0; i < m; i++)
	{
		int first_nonzero = swap_down(input, m, n, i);
		if (first_nonzero == -1)
		{
			break;
		}
		zero_down(input, m, aug_n, i, first_nonzero);
	}
}

void jordan(double** input, int m, int n, int aug_n)
{
	for (int i = m - 1; i >= 0; i--)
	{
		one_here_zero_up(input, m, n, aug_n, i);
	}
}

int swap_down(double** input, int m, int n, int row)
{
	for (int i = row; i < n; i++)
	{
		if (input[row][i] != 0)
		{
			return i;
		}
		for (int j = row + 1; j < m; j++)
		{
			if (input[j][i] != 0)
			{
				double* temp = input[row];
				input[row] = input[j];
				input[j] = temp;
				return i;
			}
		}
	}
	return -1;
}

void zero_down(double** input, int m, int aug_n, int row, int first_nonzero)
{
	#pragma omp parallel for
	for (int i = row + 1; i < m; i++)
	{
		double factor = input[i][first_nonzero] / input[row][first_nonzero];
		#pragma omp parallel for
		for (int j = first_nonzero; j < aug_n; j++)
		{
			input[i][j] -= factor * input[row][j];
		}
	}
}

void one_here_zero_up(double** input, int m, int n, int aug_n, int row)
{
	for(int i = row; i < n; i++)
	{
		if (input[row][i] == 0)
		{
			continue;
		}
		double one_factor = 1 / input[row][i];
		#pragma omp parallel for
		for (int j = i; j < aug_n; j++)
		{
			input[row][j] *= one_factor;
		}
		#pragma omp parallel for
		for (int j = row - 1; j >= 0; j--)
		{
			double zero_factor = input[j][i];
			#pragma omp parallel for
			for (int k = i; k < aug_n; k++)
			{
				input[j][k] -= zero_factor * input[row][k];
			}
		}
	}
}