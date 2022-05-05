

#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
    int ProcNum, ProcRank, RecvRank;
    MPI_Status Status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	int N = 1790;
	int chunk = N / (ProcNum-1);
	int M = 230;

    if (ProcRank == 0)
    {
        // Действия, выполняемые только процессом с рангом 0
		double all_sum = 0.0;

        for (int i = 1; i < ProcNum; i++)
        {
            double data;
            // получение сообщения из ресурса под номером i
            MPI_Recv(&data, 1, MPI_DOUBLE, i,
                     MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

			all_sum += data;
        }
		
		printf("Computed SUM = %f\n", all_sum);
    }
	else if(ProcRank == (ProcNum-1))
	{
		printf("LAST\n");
		int remainder = N % chunk;
		int iter = ProcRank - 1;
		int start = 1 + chunk * iter;
		int end = 1 + chunk * (iter+1) + remainder;

		double result = 0.0;

		for(int i=start; i < end; i++)
		{
			for(int j=1; j < M; j++)
			{
				result += (double)(1/((double)(i*i) + (double)(j*j*j)));
			}
		}

		MPI_Send(&result, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
    else
    {	
		int iter = ProcRank - 1;
		int start = 1 + chunk * iter;
		int end = 1 + chunk * (iter+1);

		double result = 0.0;

		for(int i=start; i < end; i++)
		{
			for(int j=1; j < M; j++)
			{
				result += (double)(1/((double)(i*i) + (double)(j*j*j)));
			}
		}

        MPI_Send(&result, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}