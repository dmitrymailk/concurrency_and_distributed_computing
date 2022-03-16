#include <stdio.h>
int main(int argc, char *argv[])
{
	int count = 0;
#pragma omp parallel reduction(+ \
							   : count)
	{
		count++;
		printf("Текущее значение count: %d\n", count);
	}
	printf("Число нитей: %d\n", count);
}