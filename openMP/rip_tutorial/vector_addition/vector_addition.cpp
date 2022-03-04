#include <omp.h>
#include <stdio.h>
#include <iostream>

void parallelAddition(unsigned N, const double *A, const double *B, double *C)
{
	unsigned i;

#pragma omp parallel for shared(A, B, C, N) private(i) schedule(static)
	for (i = 0; i < N; ++i)
	{
		C[i] = A[i] + B[i];
	}
}

int main(int argc, char *argv[])
{
	double *A, *B, *C;
	unsigned N = 10000000;

	A = new double[N];
	B = new double[N];
	C = new double[N];

	for (unsigned i = 0; i < N; i++)
	{
		A[i] = 1 + i % 19;
		B[i] = 1 + i % 17;
	}

	parallelAddition(N, A, B, C);
	unsigned sum = 0;
	for (unsigned i = 0; i < N; i++)
	{
		sum += C[i];
	}

	std::cout << sum << " \n";

	return 0;
}