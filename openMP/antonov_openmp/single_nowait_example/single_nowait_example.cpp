#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	omp_set_num_threads(3);
#pragma omp parallel
	{
		printf("Сообщение 1\n");
		// это значит что только один thread исполнит данный код и
		// не дожидаясь завершенения выполнения области single напечатают текст
		// Сообщение 2, если же nowait убрать тогда "Сообщение 2" не появится до
		// надпись "Одна нить"
#pragma omp single nowait
		{
			printf("Одна нить\n");
		}
		printf("Сообщение 2\n");
	}
}