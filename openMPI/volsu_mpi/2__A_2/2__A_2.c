/*

2°. В главном процессе дан набор вещественных чисел; количество чисел равно количеству
подчиненных процессов. С помощью функции MPI_Send переслать по одному числу в каждый из
подчиненных процессов (первое число в процесс 1, второе — в процесс 2, и т. д.) и вывести в
подчиненных процессах полученные числа

*/

#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ProcNum, ProcRank, RecvRank;
    MPI_Status Status;

    double time_mpi_start = MPI_Wtime();

    srand(time(NULL)); // Initialization, should only be called once.
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    if (ProcRank == 0)
    {
        // Действия, выполняемые только процессом с рангом 0
        printf("Hello from process %3d\n", ProcRank);
        double *data = (double *)calloc(ProcNum - 1, sizeof(double));

        for (int i = 0; i < ProcNum - 1; i++)
        {
            int r = rand();
            data[i] = ((double)r / (double)100);
        }

        for (int i = 1; i < ProcNum; i++)
        {
            // получение сообщение из любого ресурса
            // MPI_Recv(&RecvRank, 1, MPI_INT, MPI_ANY_SOURCE,
            //          MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

            // получение сообщения из ресурса под номером i

            MPI_Send(&data[i - 1], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            printf("Send from process %3d number %f to %d \n ", ProcRank, data[i - 1], i);
        }
    }
    else
    {
        // Сообщение, отправляемое всеми процессами,
        // кроме процесса с рангом 0
        double receive_data;
        MPI_Recv(&receive_data, 1, MPI_DOUBLE, 0,
                 MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

        printf("receive_data %f from process %3d\n", receive_data, ProcRank);
    }

    MPI_Finalize();
    return 0;
}