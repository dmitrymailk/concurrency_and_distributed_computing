#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	int count = 0;
#pragma omp parallel
	{
#pragma omp atomic
		count++;
	}
	printf("Число нитей: %d\n", count);
}