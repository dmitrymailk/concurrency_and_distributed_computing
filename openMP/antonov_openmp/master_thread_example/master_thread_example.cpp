#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	int n;
	omp_set_num_threads(3);
#pragma omp parallel private(n)
	{
		n = 1;
#pragma omp master
		{
			n = 2;
		}
		printf("Первое значение n: %d\n", n);
#pragma omp barrier
// дирректива master будет выполнятся только master потоком,
// остальные же потоки проигнорируют его
// в данном случае n локальная переменная и изменив ее только в master мы
// получаем вывод 2 и 3 в master ветке, а в остальных 1
#pragma omp master
		{
			n = 3;
		}
		printf("Второе значение n: %d\n", n);
	}
}