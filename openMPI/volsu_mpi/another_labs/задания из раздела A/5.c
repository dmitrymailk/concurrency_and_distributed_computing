#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv)
{
    int procNum, procRank, recvRank;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        for (int i = 1; i < procNum; i++) {
            int number;
            MPI_Recv(&number, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Recv(&recvRank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if (recvRank == 2) {
				// cout << endl << "Rank - " << recvRank << " Number: " << number;
				printf("Rank - %d Number: %d\n", recvRank, number);
			}
        }
    }
    else if (procRank == 2) {
        int number = 228;
        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&procRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else {
        int number = 0;
        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&procRank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
