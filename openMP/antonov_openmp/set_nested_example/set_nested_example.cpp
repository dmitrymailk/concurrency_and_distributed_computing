#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	int n;
	// сокращаем количество для более наглядного вывода в консоль
	omp_set_num_threads(3);
	omp_set_nested(1);
#pragma omp parallel private(n)
	{
		n = omp_get_thread_num();
#pragma omp parallel
		{
			printf("Часть 1, нить %d - %d\n", n,
				   omp_get_thread_num());
		}
	}
	omp_set_nested(0);
#pragma omp parallel private(n)
	{
		n = omp_get_thread_num();
#pragma omp parallel
		{
			printf("Часть 2, нить %d - %d\n", n,
				   omp_get_thread_num());
		}
	}
}