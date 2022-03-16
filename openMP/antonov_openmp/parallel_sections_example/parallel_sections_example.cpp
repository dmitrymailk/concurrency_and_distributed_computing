#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	omp_set_num_threads(5);
	int n;
#pragma omp parallel private(n)
	{
		n = omp_get_thread_num();
#pragma omp sections
		{
#pragma omp section
			{
				printf("Первая секция, процесс %d\n", n);
			}
#pragma omp section
			{
				printf("Вторая секция, процесс %d\n", n);
			}
#pragma omp section
			{
				printf("Третья секция, процесс %d\n", n);
			}
		}
		printf("Параллельная область, процесс %d\n", n);
	}
}