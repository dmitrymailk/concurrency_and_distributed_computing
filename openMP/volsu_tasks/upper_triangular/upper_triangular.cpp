#include <omp.h>
#include <stdio.h>
#include <iostream>

int main()
{
	int N = 10;
	double **matrix = new double *[N];
	for (int i = 0; i < N; i++)
	{
		matrix[i] = new double[N];
	}

	for (int i = 0; i < N; i++)
	{
		for (int k = 0; k < i; k++)
			matrix[i][k] = 0;

		for (int j = i; j < N; j++)
			matrix[i][j] = (double)(1);
	}

	double sum = 0;
	double total = 0;
	int i, j;

#pragma omp parallel for private(sum, i, j) reduction(+ \
													  : total)
	for (i = 0; i < N; i++)
	{
		sum = 0;
		for (j = i; j < N; j++)
		{
			sum += matrix[i][j];
		}
		total += sum;
	}

	std::cout
		<< total << " <- result\n";

	return 0;
}