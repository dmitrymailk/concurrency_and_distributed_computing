#include "../../MPI/Include/mpi.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL); // Initialize MPI

    // // get number of processes
    // int world_size;
    // MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // // get my process's rank
    // int world_rank;
    // MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // printf("Hello, world. - Love, process %d/%d \n",
    //        world_rank, world_size);

    // MPI_Finalize(); // Clean-up
}