#include "mpi.h"
#include <stdio.h>


int main(int argc, char** argv)
{
    int procNum, procRank, recvRank;
    const int bufSize = 100;
    double* buf[bufSize];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    if (procRank == 0)
    {
        double sendNum = 228.1,
            recvNum;


        for (int i = 1; i < procNum; i++)
        {
            MPI_Recv(&recvNum, 1, MPI_DOUBLE, i, 10, MPI_COMM_WORLD, &status);
            printf("Rank[%d]: %lf - from proc\n", i, recvNum);
            MPI_Send(&sendNum, 1, MPI_DOUBLE, i, 11, MPI_COMM_WORLD);
        }
    }
    else
    {
        double sendNum = procRank, recvNum;

        sendNum = (double)sendNum;

        MPI_Send(&sendNum, 1, MPI_DOUBLE, 0, 10, MPI_COMM_WORLD);

        MPI_Recv(&recvNum, 1, MPI_DOUBLE, 0, 11, MPI_COMM_WORLD, &status);
        printf("Rank[%d]: %lf - from main\n", procRank, recvNum);
    }
    MPI_Finalize();
}
