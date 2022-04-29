#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv)
{
    int procNum, procRank, recvRank;
    MPI_Status status;
    
    int posNumbers = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    if (procRank == 0) {
        int sum = 0;
        for (int i = 1; i < procNum; i++) {
			int data[2];
            MPI_Recv(&data, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            int number = data[0];
            // MPI_Recv(&recvRank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if (number > 0) {
                posNumbers += 1;
                sum += number;
            }
        }
		printf("overall positive numbers => %d\n", posNumbers);
		printf("sum of positive numbers => %d\n", sum);
    }
    else {
		int arrInt[4] = {-2, 6, -5, 10};
        int number = arrInt[procRank - 1];
		printf("%d\n", procRank-1);
		int data[2] = {number, procRank};
        MPI_Send(&data, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
