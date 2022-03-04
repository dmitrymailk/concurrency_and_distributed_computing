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
#pragma omp parallel
	{
#pragma omp for
		for (i = 0; i < MAX; i++)
		{
			res[i] = huge();
		}
	}

	for (int i = 0; i < MAX; i++)
	{
		result += res[i];
	}

	std::cout
		<< result << " <- result\n";

	return 0;
}