#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	omp_set_num_threads(3);
	int n = 1;
	printf("Значение n в начале: %d\n", n);

#pragma omp parallel firstprivate(n)
	{
		printf("Значение n на нити (на входе): %d\n", n);
		/* Присвоим переменной n номер текущей нити */
		n = omp_get_thread_num();
		printf("Значение n на нити (на выходе): %d\n", n);
	}
	printf("Значение n в конце: %d\n", n);
}