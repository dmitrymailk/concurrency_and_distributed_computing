#include <stdio.h>
#include "mpi.h"
#include <math.h>

double function(double x)
{
	return x*x + x;
}

int main(int argc, char **argv)
{
	int procNum, procRank, recvRank;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

	double start = 1;
	double end = 10;
	double n = 100;
	double chunk = (double)((end - start) / (double)(procNum-1));
	
	if (procRank == 0)
	{
		double all_integral = 0;
		for (int i = 1; i < procNum; i++)
		{
			double number;
			MPI_Recv(&number, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			all_integral += number;
		}
		printf("Integral result %f \n", all_integral);
	}
	else
	{
		int part = procRank - 1;
		double number = 0.0;
		double a = start + part * chunk;
		double b = start + (part+1) * chunk;

		double h = (b - a) / n;

		for (int i = 0; i < n; i++)
		{
			number += function(a + h * (i + 0.5));
		}

		number *= h;

		MPI_Send(&number, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
