/*

3°. В каждом подчиненном процессе даны четыре целых числа. Переслать эти числа в главный
процесс, используя по одному вызову функции MPI_Send для каждого передающего процесса, и
вывести их в главном процессе. Полученные числа выводить в порядке возрастания рангов
переславших их процессов.

*/

#include <stdio.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ProcNum, ProcRank, RecvRank;
    MPI_Status Status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    if (ProcRank == 0)
    {
        // Действия, выполняемые только процессом с рангом 0
        for (int i = 1; i < ProcNum; i++)
        {
            // получение сообщение из любого ресурса
            // MPI_Recv(&RecvRank, 1, MPI_INT, MPI_ANY_SOURCE,
            //          MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

            // получение сообщения из ресурса под номером i
            int some[4];
            MPI_Recv(&some, 4, MPI_INT, i,
                     MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
            for (int j = 0; j < 4; j++)
            {
                printf("receive data from %d - data=%d\n", i, some[j]);
            }
            printf("\n");
            // printf("Hello from process %3d\n", RecvRank);
        }
    }
    else
    {
        // Сообщение, отправляемое всеми процессами,
        // кроме процесса с рангом 0
        // int some[] = {1, 2, 3, 4};
        int some[4];
        for (int i = 0; i < 4; i++)
        {
            some[i] = i + ProcRank;
            // print("Send from %");
        }

        MPI_Send(&some, 4, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    // double time_mpi_end = MPI_Wtime();
    // printf("Working time is %f on host %d\n", time_mpi_end - time_mpi_start, ProcRank);
    return 0;
}