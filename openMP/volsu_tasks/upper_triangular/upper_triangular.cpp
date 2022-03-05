#include <omp.h>
#include <stdio.h>
#include <iostream>

void schedule_static()
{
	std::cout << "schedule_static\n";
	int N = 10000;
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
	double tbegin = omp_get_wtime();

#pragma omp parallel for private(sum, i, j) reduction(+ \
													  : total) schedule(static)
	for (i = 0; i < N; i++)
	{
		sum = 0;
		for (j = i; j < N; j++)
		{
			sum += matrix[i][j];
		}

		// #pragma omp critical
		// 		std::cout
		// 			<< "row sum is " << sum
		// 			<< " thread id " << omp_get_thread_num()
		// 			<< " row num -> " << i
		// 			<< "\n";
		total += sum;
	}
	double tend = omp_get_wtime();
	std::cout
		<< total << " <- result\n"
		<< tend - tbegin << " <- time execution"
		<< "\n";
}
void schedule_dynamic()
{

	std::cout << "schedule_dynamic\n";
	int N = 10000;
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
	double tbegin = omp_get_wtime();

#pragma omp parallel for private(sum, i, j) reduction(+ \
													  : total) schedule(dynamic)
	for (i = 0; i < N; i++)
	{
		sum = 0;
		for (j = i; j < N; j++)
		{
			sum += matrix[i][j];
		}

		// #pragma omp critical
		// 		std::cout
		// 			<< "row sum is " << sum
		// 			<< " thread id " << omp_get_thread_num()
		// 			<< " row num -> " << i
		// 			<< "\n";
		total += sum;
	}
	double tend = omp_get_wtime();
	std::cout
		<< total << " <- result\n"
		<< tend - tbegin << " <- time execution"
		<< "\n";
}

void schedule_guided()
{
	std::cout << "schedule_guided\n";

	int N = 10000;
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
	double tbegin = omp_get_wtime();

#pragma omp parallel for private(sum, i, j) reduction(+ \
													  : total) schedule(guided, 2)
	for (i = 0; i < N; i++)
	{
		sum = 0;
		for (j = i; j < N; j++)
		{
			sum += matrix[i][j];
		}

		// #pragma omp critical
		// 		std::cout
		// 			<< "row sum is " << sum
		// 			<< " thread id " << omp_get_thread_num()
		// 			<< " row num -> " << i
		// 			<< "\n";
		total += sum;
	}
	double tend = omp_get_wtime();
	std::cout
		<< total << " <- result\n"
		<< tend - tbegin << " <- time execution"
		<< "\n";
}

int main()
{

	schedule_static();
	schedule_dynamic();

	// bad alloc error
	// schedule_guided();

	return 0;
}