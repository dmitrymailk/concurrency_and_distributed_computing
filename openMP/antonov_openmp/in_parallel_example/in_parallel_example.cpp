#include <stdio.h>
#include <omp.h>
void mode(void)
{
	if (omp_in_parallel())
		printf("Параллельная область\n");
	else
		printf("Последовательная область\n");
}

int main(int argc, char *argv[])
{
	mode();
#pragma omp parallel
	{
#pragma omp master
		{
			mode();
		}
	}
}