#include <iostream>
#include <omp.h>

using namespace std;

int determinant(int const * const * input, int full_size, int sub_size, int const * columns)
{
	if (full_size < 1)
	{
		cout << "Error: cannot calculate the determinant of a matrix of size " << full_size << "." << endl;
		return 0;
	}
	else if (sub_size < 1)
	{
		cout << "Error: cannot calculate the minor of a submatrix of size " << sub_size << "." << endl;
		return 0;
	}
	else if (full_size == 1)
	{
		return input[0][0];
	}
	else if (sub_size == 1)
	{
		return input[full_size - sub_size][columns[0]];
	}
	else if (sub_size > full_size)
	{
		cout << "Error: cannot calculate the minor of a submatrix of size " << sub_size << ", which is larger than the matrix of size " << full_size << "." << endl;
		return 0;
	}
	else
	{
		int sub_list_size = (sub_size == full_size || !columns) ? full_size : sub_size;
		int * sub_list = (int *)malloc(sub_list_size * sizeof(int));
		#pragma omp parallel for
		for (int i = 0; i < sub_list_size; i++)
		{
			int * sub_columns = (int*)malloc((sub_list_size - 1) * sizeof(int));
			#pragma omp parallel for
			for (int j = 0; j < sub_list_size - 1; j++)
			{
				if (j < i)
				{
					sub_columns[j] = (sub_size == full_size || !columns) ? j : columns[j];
				}
				else
				{
					sub_columns[j] = (sub_size == full_size || !columns) ? j + 1 : columns[j + 1];
				}
			}
			sub_list[i] = (sub_size == full_size || !columns) ? determinant(input, full_size, full_size - 1, sub_columns) : determinant(input, full_size, sub_size - 1, sub_columns);
			free(sub_columns);
		}
		int sum = 0;
		#pragma omp parallel for reduction (+:sum)
		for (int i = 0; i < sub_list_size; i++)
		{
			int column_index = (sub_size == full_size || !columns) ? i : columns[i];
			if (i % 2 == 0)
			{
				sum += input[full_size - sub_size][column_index] * sub_list[i];
			}
			else
			{
				sum += -1 * input[full_size - sub_size][column_index] * sub_list[i];
			}
		}
		free(sub_list);
		return sum;
	}
}