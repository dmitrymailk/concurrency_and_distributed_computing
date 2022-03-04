#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
#pragma omp parallel
	{
		printf("Hello world! I'm thread %d out of %d threads.\n",
			   omp_get_thread_num(), omp_get_num_threads());
	}
	return 0;
}