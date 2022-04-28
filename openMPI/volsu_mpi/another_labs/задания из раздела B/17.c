#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    int procNum, procRank, recvRank;
    const int bufSize = 100;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

    int buf = procRank;

    if (procRank == 0)
    {
        MPI_Ssend(&buf, 1, MPI_INT, procRank + 1, 10, MPI_COMM_WORLD);

        MPI_Recv(&buf, 1, MPI_INT, procNum - 1, 10, MPI_COMM_WORLD, &status);
        printf("Rank[%d]: %d\n", procRank, buf);
    }
    else if (procRank == procNum - 1)
    {
        MPI_Recv(&buf, 1, MPI_INT, procRank - 1, 10, MPI_COMM_WORLD, &status);
        printf("Rank[%d]: %d\n", procRank, buf);

        buf = procRank;
        MPI_Ssend(&buf, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(&buf, 1, MPI_INT, procRank - 1, 10, MPI_COMM_WORLD, &status);
        printf("Rank[%d]: %d\n", procRank, buf);

        buf = procRank;
        MPI_Ssend(&buf, 1, MPI_INT, procRank + 1, 10, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
