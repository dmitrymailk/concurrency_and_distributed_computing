

#include <stdio.h>
#include "mpi.h"
int main(int argc, char *argv[])
{
    int ProcNum, ProcRank, RecvRank;
    MPI_Status Status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	int chunk = 10000;

    if (ProcRank == 0)
    {
        // Действия, выполняемые только процессом с рангом 0
		long double all_pi = 0.0;

        for (int i = 1; i < ProcNum; i++)
        {
            long double process_pi;
            // получение сообщения из ресурса под номером i
            MPI_Recv(&process_pi, 1, MPI_LONG_DOUBLE, i,
                     MPI_ANY_TAG, MPI_COMM_WORLD, &Status);

			all_pi += process_pi;
        }
		
		printf("Computed pi^2/6 = %Lf\n", all_pi);
    }
    else
    {	
		int iter = ProcRank - 1;
		int start = 1 + chunk * iter;
		int end = 1 + chunk * (iter+1);

		long double result = 0.0;

		for(int n=start; n < end; n++)
		{
			result += (long double)(1 / (long double)(n*n)); 
		}

        MPI_Send(&result, 1, MPI_LONG_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}