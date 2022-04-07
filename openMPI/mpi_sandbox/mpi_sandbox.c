#include <mpi.h>
#include <stdio.h>
#define my_maroc 123

int main(int argc, char **argv)
{
	// Initialize the MPI environment
	MPI_Init(NULL, NULL);

	// возвращает общее количество процессов
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Get the rank of the process
	// указывает номер процесса, вызывающего эту процедуру.
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// Get the name of the processor
	char processor_name[10];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	// Print off a hello world message
	printf("Hello world from processor %s, rank %d out of %d processors\n",
		   processor_name, world_rank, world_size);

	// communicator
	// MPI_Comm comm = MPI_COMM_WORLD;
	// MPI_Send(comm);

	// Finalize the MPI environment.
	MPI_Finalize();
}