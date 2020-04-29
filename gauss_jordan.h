#pragma once

void gauss_jordan(double** input, int m, int n, int aug_n);
void gauss(double** input, int m, int n, int aug_n);
void jordan(double** input, int m, int n, int aug_n);
int swap_down(double** input, int m, int n, int row);
void zero_down(double** input, int m, int aug_n, int row, int first_nonzero);
void one_here_zero_up(double** input, int m, int n, int aug_n, int row);