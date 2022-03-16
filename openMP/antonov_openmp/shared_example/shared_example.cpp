#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	omp_set_num_threads(2);
	int length = 5;
	int i, m[length];
	printf("Массив m в начале:\n");

	/* Заполним массив m нулями и напечатаем его */
	for (i = 0; i < length; i++)
	{
		m[i] = 0;
		printf("%d\n", m[i]);
	}

#pragma omp parallel shared(m)
	{
		/* Присвоим 1 элементу массива m, номер которого
		совпадает с номером текущий нити */
		int pos = omp_get_thread_num();
		m[pos] = 1;
	}

	/* Ещё раз напечатаем массив */
	printf("Массив m в конце:\n");
	for (i = 0; i < length; i++)
		printf("%d\n", m[i]);
}