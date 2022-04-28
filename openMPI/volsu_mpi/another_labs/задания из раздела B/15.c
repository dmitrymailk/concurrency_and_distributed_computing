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

	if (procRank == 0)
	{
		for (int i = procNum - 1; i >= 1; i--)
		{
			MPI_Status status;
			int *recvNumbers = malloc(bufSize * sizeof(int));

			MPI_Recv(recvNumbers, bufSize, MPI_INT, i, 10, MPI_COMM_WORLD, &status);

			int count;
			MPI_Get_count(&status, MPI_INT, &count);

			for (int j = 0; j < count; j++)
			{
				printf("Rank[%d]: %d\n", i, recvNumbers[j]);
			}
		}
	}
	else
	{
		int *sendNumbers;

		int seed = rand() % 5;
		int N = seed + procRank;

		sendNumbers = malloc(N * sizeof(int));

		for (int i = 0; i < N; i++)
		{
			int seed = rand() % procRank;
			sendNumbers[i] = seed * 3 + 5;
		}

		MPI_Send(sendNumbers, N, MPI_INT, 0, 10, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
