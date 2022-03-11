#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{

#pragma omp parallel
	{
		int t = omp_get_thread_num();
		printf("Hello world from %d!\n", t);
	}

	return 0;
}
