#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	omp_set_num_threads(4);
	int count, num;
#pragma omp parallel
	{
		count = omp_get_num_threads();
		num = omp_get_thread_num();
		if (num == 0)
			printf("Всего нитей: %d\n", count);
		else
			printf("Нить номер %d\n", num);
	}
}