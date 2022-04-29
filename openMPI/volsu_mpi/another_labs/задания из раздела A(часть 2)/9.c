#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    int procNum, procRank, recvRank;
    MPI_Status status;
    int arrInt[] = {0, 0, 1, 0, 0};
    int posNumbers = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
    int number = arrInt[procRank];
    if (number == 1) {
        int currentProc = procRank;
        int arrNumbers[4] = { 5, 8, 9, 15 };
        int sendProc = 0;
        for (int i = 0; i < 4; i++) {
            if (currentProc == i) {
                sendProc++;
            }
			int data[2] = {arrNumbers[i], procRank}; 
            // MPI_Send(&arrNumbers[i], 1, MPI_INT, sendProc, 0, MPI_COMM_WORLD);
            // MPI_Send(&procRank, 1, MPI_INT, sendProc, 0, MPI_COMM_WORLD);
            MPI_Send(&data, 2, MPI_INT, sendProc, 0, MPI_COMM_WORLD);
            sendProc++;
        }
    }
    else if (number == 0)
    {
        int recvNumber;
		int data[2];
        MPI_Recv(&data, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		recvNumber = data[0];
		recvRank = data[1];
		printf("Received data: %d - from source %d\n", recvNumber, recvRank);
    }
    MPI_Finalize();
}
