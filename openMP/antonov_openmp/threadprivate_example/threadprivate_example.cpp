#include <stdio.h>
#include <omp.h>
int n;
#pragma omp threadprivate(n)
int main(int argc, char *argv[])
{
	omp_set_num_threads(3);
	int num;
	n = 1;
#pragma omp parallel private(num)
	{
		num = omp_get_thread_num();
		printf("Значение n на нити %d (на входе): %d\n", num, n);
		/* Присвоим переменной n номер текущей нити */
		n = omp_get_thread_num();
		printf("Значение n на нити %d (на выходе): %d\n", num, n);
	}
	printf("Значение n (середина): %d\n", n);
	// значение n сохраняется даже после завержения параллельной секции
	// отдельно для каждого потока своё значение n
#pragma omp parallel private(num)
	{
		num = omp_get_thread_num();
		printf("Значение n на нити %d (ещё раз): %d\n", num, n);
	}
}