#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>



int main(int argc, char **argv)
{
	int procNum, procRank, recvRank;
	const int bufSize = 100;
	double *buf[bufSize];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

	double sendNumber;
	double recvNumber;

	if (procRank == 0)
	{
		for (int i = procNum - 1; i >= 1; i--)
		{
			MPI_Recv(&recvNumber, 1, MPI_DOUBLE, i, 10, MPI_COMM_WORLD, &status);
			printf("Rank[%d]: %lf\n", i, recvNumber);
		}
	}
	else
	{
		MPI_Buffer_attach(malloc(bufSize), bufSize);
		sendNumber = procRank + 1 * 3;
		MPI_Bsend(&sendNumber, 1, MPI_DOUBLE, 0, 10, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
