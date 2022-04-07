#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
    int ProcNum, ProcRank, RecvRank;
    MPI_Status Status;

    double time_mpi_start = MPI_Wtime();

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    if (ProcRank == 0)
    {
        // Действия, выполняемые только процессом с рангом 0
        printf("Hello from process %3d\n", ProcRank);
        for (int i = 1; i < ProcNum; i++)
        {
            // получение сообщение из любого ресурса
            // MPI_Recv(&RecvRank, 1, MPI_INT, MPI_ANY_SOURCE,
            //          MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

            // получение сообщения из ресурса под номером i
            MPI_Recv(&RecvRank, 1, MPI_INT, i,
                     MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

            printf("Hello from process %3d\n", RecvRank);
        }
    }
    else
    {
        // Сообщение, отправляемое всеми процессами,
        // кроме процесса с рангом 0
        MPI_Send(&ProcRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    double time_mpi_end = MPI_Wtime();
    printf("Working time is %f on host %d\n", time_mpi_end - time_mpi_start, ProcRank);
    return 0;
}