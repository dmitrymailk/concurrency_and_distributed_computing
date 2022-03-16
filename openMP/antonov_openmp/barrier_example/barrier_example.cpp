#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	omp_set_num_threads(3);
#pragma omp parallel
	{
		printf("Сообщение 1\n");
		printf("Сообщение 2\n");
		// позволяет убедиться что все блоки до выполнили свои части кода
#pragma omp barrier
		printf("Сообщение 3\n");
	}
}