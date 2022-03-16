#include <stdio.h>
#include <omp.h>
#include <unistd.h>

omp_lock_t lock;
int main(int argc, char *argv[])
{
	omp_set_num_threads(3);
	int n;
	omp_init_lock(&lock);
#pragma omp parallel private(n)
	{
		n = omp_get_thread_num();
		omp_set_lock(&lock);
		printf("Начало закрытой секции, нить %d\n", n);
		sleep(1);
		printf("Конец закрытой секции, нить %d\n", n);
		omp_unset_lock(&lock);
	}
	omp_destroy_lock(&lock);
}