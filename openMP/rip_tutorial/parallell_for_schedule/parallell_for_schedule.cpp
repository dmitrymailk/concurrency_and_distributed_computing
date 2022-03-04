#include <omp.h>
#include <stdio.h>
#include <iostream>

double huge()
{
	double some = 0;
	for (int i = 0; i < 100; i++)
		some += 1 / (double)3;
	return some;
}

int main(int argc, char *argv[])
{
	int MAX = 1000;
	double res[MAX];
	int i;
	double result = 0;
/**
 * schedule(static [,chunk])
 * Deal-out blocks of iterations of size “chunk” to each thread.
 * If not specified: allocate as evenly as possible to the available threads
 *
 * schedule(dynamic[,chunk])
 * Each thread grabs “chunk” iterations off a queue until all iterations have been handled.
 *
 * schedule(guided[,chunk])
 * Threads dynamically grab blocks of iterations. The size of the block starts large and shrinks down
 * to size “chunk” as the calculation proceeds.
 *
 * schedule(runtime)
 * Schedule and chunk size taken from the OMP_SCHEDULE environment variable.
 */
#pragma omp parallel for schedule(static)
	for (i = 0; i < MAX; i++)
	{
		res[i] = huge();
	}

	for (int i = 0; i < MAX; i++)
	{
		result += res[i];
	}

	std::cout
		<< result << " <- result\n";

	return 0;
}