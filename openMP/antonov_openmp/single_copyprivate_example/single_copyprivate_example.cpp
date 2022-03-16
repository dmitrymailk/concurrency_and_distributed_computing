#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	int n;
	omp_set_num_threads(2);
#pragma omp parallel private(n)
	{
		n = omp_get_thread_num();
		printf("Значение n (начало): %d\n", n);

		// один поток присвоит значение переменной 100
		// а и при выходе из блока оно будет присвоено 100 на всех остальных потоках
#pragma omp single copyprivate(n)
		{
			n = 100;
		}
		printf("Значение n (конец): %d\n", n);
	}
}