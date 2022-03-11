#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel
	{
		printf("Hello from parallel\n");
	}

	printf("----- SINGLE EXECUTION ------\n");

#pragma omp parallel
	{
#pragma omp single
		printf("Hello from parallel\n");
	}
}