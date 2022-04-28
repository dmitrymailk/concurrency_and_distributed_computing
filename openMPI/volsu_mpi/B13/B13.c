#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    // Get the number of processes and check only 2 are used.
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
 
    // Get my rank and do the corresponding job
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    switch(my_rank)
    {
        case 0:
        {
			for(int sender_id=1; sender_id < size; sender_id++)
			{
				float received;

				MPI_Recv(&received, 1, MPI_FLOAT, sender_id, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf("[MPI process %d] I received value: %f.\n", my_rank, received);
				// for(int i=0; i<5; i++)
				// {
				// }
			}
            // Receive the message and print it.
            break;
        }
        default:
        {
            // Declare the buffer and attach it
            int buffer_attached_size = MPI_BSEND_OVERHEAD + sizeof(float);
            float* buffer_attached = (float*)malloc(buffer_attached_size);
            MPI_Buffer_attach(buffer_attached, buffer_attached_size);
 
            // Issue the MPI_Bsend
            // float buffer_sent[5];
			// for(int i=0; i<5; i++)
			// {
			// 	buffer_sent[i] = (float)(my_rank + i);
			// }
			float buffer_sent = (float)my_rank + (float)(rand() % 100);

            printf("[MPI process %d] I send value %f.\n", my_rank, buffer_sent);
            MPI_Bsend(&buffer_sent, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
 
            // Detach the buffer. It blocks until all messages stored are sent.
            MPI_Buffer_detach(&buffer_attached, &buffer_attached_size);
            free(buffer_attached);
            break;
        }
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}