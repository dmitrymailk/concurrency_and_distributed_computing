#include <stdio.h>
#include <omp.h>
int n;
#pragma omp threadprivate(n)
int main(int argc, char *argv[])
{
	omp_set_num_threads(3);
	n = 1;
	// copyin копирует начальное значение в каждую переменную
#pragma omp parallel copyin(n)
	{
		printf("Значение n: %d\n", n);
	}
}