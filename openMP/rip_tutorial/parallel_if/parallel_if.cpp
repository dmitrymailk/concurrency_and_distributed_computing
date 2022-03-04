#include <omp.h>
#include <stdio.h>

int main(void)
{
	int t = true;  // true value
	int f = false; // false value

#pragma omp parallel if (f)
	{
		printf("FALSE: I am thread %d\n", omp_get_thread_num());
	}

#pragma omp parallel if (t)
	{
		printf("TRUE : I am thread %d\n", omp_get_thread_num());
	}
	return 0;
}
