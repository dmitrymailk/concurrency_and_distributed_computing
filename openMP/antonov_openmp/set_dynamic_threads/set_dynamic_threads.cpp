#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	printf("Значение OMP_DYNAMIC: %d\n", omp_get_dynamic());
	omp_set_dynamic(1);
	printf("Значение OMP_DYNAMIC: %d\n", omp_get_dynamic());
#pragma omp parallel num_threads(16)
	{
#pragma omp master
		{
			printf("Параллельная область, %d нитей доступных процессов %d\n",
				   omp_get_num_threads(), omp_get_num_procs());
		}
	}
}