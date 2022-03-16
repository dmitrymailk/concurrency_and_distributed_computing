#include <stdio.h>
int main(int argc, char *argv[])
{
	printf("Последовательная область 1\n");
#pragma omp parallel
	{
		printf("Параллельная область\n");
	}
	printf("Последовательная область 2\n");
}