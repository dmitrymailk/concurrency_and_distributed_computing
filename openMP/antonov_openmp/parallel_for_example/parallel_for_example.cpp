#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	omp_set_num_threads(3);
	int A[10], B[10], C[10], i, n;
	/* Заполним исходные массивы */
	for (i = 0; i < 10; i++)
	{
		A[i] = i;
		B[i] = 2 * i;
		C[i] = 0;
	}

#pragma omp parallel shared(A, B, C) private(i, n)
	{
		/* Получим номер текущей нити */
		n = omp_get_thread_num();
#pragma omp for // schedule(dynamic)
		for (i = 0; i < 10; i++)
		{
			C[i] = A[i] + B[i];
			printf("Нить %d сложила элементы с номером %d\n",
				   n, i);
		}
	}
}