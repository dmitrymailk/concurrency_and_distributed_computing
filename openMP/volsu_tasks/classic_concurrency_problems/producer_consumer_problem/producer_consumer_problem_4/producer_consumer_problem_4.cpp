// https://youtu.be/l6zkaJFjUbM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#define THREAD_NUM 8

omp_lock_t lock;

void *producer(int *buffer, int count)
{
	while (1)
	{
		// Produce
		int x = rand() % 100;
		sleep(1);

		// Добавление данных в буфер
		omp_set_lock(&lock);
		buffer[count] = x;
		count++;
		sleep(1);
		printf("Add gen num to buffer num=%d, count=%d\n", x, count);
		omp_unset_lock(&lock);
	}
}

void *consumer(int *buffer, int count)
{
	while (1)
	{
		int y;
		omp_set_lock(&lock);
		// получение данных из буфера
		y = buffer[count - 1];
		count--;
		printf("Get data from buffer %d\n", y, count);
		sleep(1);
		omp_unset_lock(&lock);

		// Обработка полученных данных
		int sum = 0;
		for (int i = 0; i < y * 1000; i++)
		{
			sum += i;
		}
		printf("Consumer sum of %d = %d\n", y, sum);
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	omp_init_lock(&lock);
	int buffer[10];
	int count = 0;
#pragma omp parallel shared(buffer, count)
	{
		int i = omp_get_thread_num();
		printf("i=%d\n", i);
		if (i > 0)
		{
			producer(buffer, count);
		}
		else
		{
			consumer(buffer, count);
		}
	}

	return 0;
}