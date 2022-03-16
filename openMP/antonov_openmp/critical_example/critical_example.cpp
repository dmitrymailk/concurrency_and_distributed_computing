/*
В каждый момент времени в критической секции может находиться не более
одной нити. Если критическая секция уже выполняется какой-либо нитью, то
все другие нити, выполнившие директиву для секции с данным именем, будут
заблокированы, пока вошедшая нить не закончит выполнение данной
критической секции. Как только работавшая нить выйдет из критической
секции, одна из заблокированных на входе нитей войдет в неё. Если на входе
в критическую секцию стояло несколько нитей, то случайным образом выбирается
одна из них, а остальные заблокированные нити продолжают ожидание.
*/
#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
	int n;
#pragma omp parallel
	{
		// стоит отметить что тут не происходит гонка данных
		// так как каждый поток ждет пока этот код исполнит другой
#pragma omp critical
		{
			n = omp_get_thread_num();
			printf("Нить %d\n", n);
		}
	}
}