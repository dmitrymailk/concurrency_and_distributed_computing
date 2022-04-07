/* ag_ring_syn.c -- ring allgather using synchronous sends and 
 *     blocking receives
 *
 * Input: series of blocksizes for allgather, 0 to stop.
 * Output: Contents of gathered array on each process -- list of
 *     process ranks, each rank appearing in a block of size blocksize.
 *
 * Note:  array sizes are hardwired in MAX and LOCAL_MAX.
 *
 * See Chap 13, pp. 305 & ff, in PPMPI.
 */

#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include "cio.h"

#define MAX 128
#define LOCAL_MAX 128

void Allgather_ring(float x[], int blocksize,
         float y[], MPI_Comm ring_comm);

void Print_arrays(MPI_Comm io_comm, char* title, 
         float y[], int blocksize);


/********************************************************************/
main(int argc, char* argv[]) {
    int       p;
    int       my_rank;
    float     x[LOCAL_MAX];
    float     y[MAX];
    int       blocksize;
    MPI_Comm  io_comm;
    int       i;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_dup(MPI_COMM_WORLD, &io_comm);
    Cache_io_rank(MPI_COMM_WORLD, io_comm);

    Cscanf(io_comm,"Enter the local array size","%d", &blocksize);

    while(blocksize > 0) {
        for (i = 0; i < blocksize; i++)
            x[i] = (float) my_rank;
        Allgather_ring(x, blocksize, y, MPI_COMM_WORLD);
        Print_arrays(io_comm, "Gathered_arrays", y, blocksize);
        /* Enter 0 to stop. */
        Cscanf(io_comm,"Enter the local array size",
            "%d", &blocksize);
    }

    MPI_Finalize();
}  /* main */


/********************************************************************/
void Allgather_ring(
         float     x[]        /* in  */, 
         int       blocksize  /* in  */, 
         float     y[]        /* out */, 
         MPI_Comm  ring_comm  /* in  */) {

    int         i, p, my_rank;
    int         successor, predecessor;
    int         send_offset, recv_offset;
    MPI_Status  status;
    
    MPI_Comm_size(ring_comm, &p);
    MPI_Comm_rank(ring_comm, &my_rank);

    /* Copy x into correct location in y */
    for (i = 0; i < blocksize; i++)
        y[i + my_rank*blocksize] = x[i];

    successor = (my_rank + 1) % p;
    predecessor = (my_rank - 1 + p) % p;

    for (i = 0; i < p - 1; i++) {
        send_offset = ((my_rank - i + p) % p)*blocksize;
        recv_offset = 
            ((my_rank - i - 1 + p) % p)*blocksize;
        if ((my_rank % 2) == 0){ /* Even ranks send first */
            MPI_Ssend(y + send_offset, blocksize, MPI_FLOAT, 
                successor, 0, ring_comm);
            MPI_Recv(y + recv_offset, blocksize, MPI_FLOAT,
               predecessor, 0, ring_comm, &status);
        } else {  /* Odd ranks receive first */
            MPI_Recv(y + recv_offset, blocksize, MPI_FLOAT,
               predecessor, 0, ring_comm, &status);
            MPI_Ssend(y + send_offset, blocksize, MPI_FLOAT, 
                successor, 0, ring_comm);
        }
    }
} /* Allgather_ring */


/********************************************************************/
void Print_arrays(
         MPI_Comm  io_comm    /* in */,
         char*     title      /* in */, 
         float     y[]        /* in */, 
         int       blocksize  /* in */) {

    char item[16];
    char list[4*MAX];
    int  i;
    int  p;

    MPI_Comm_size(io_comm, &p);

    list[0] = '\0';
    for (i = 0; i < blocksize*p; i++) {
        sprintf(item, "%3.1f ", y[i]);
        strcat(list, item);
    }
    Cprintf(io_comm, title, "%s", list);
}  /* Print_arrays */
