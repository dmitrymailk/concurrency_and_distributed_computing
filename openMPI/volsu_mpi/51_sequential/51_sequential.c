#include <mpi.h>
#include <stdio.h>
#define my_maroc 123
int main(int argc, char **argv)
{
	int N = 335;
	for (int x = -N; x < N; x++) {
		for (int y = -N; y < N; y++)
		{
			for (int z = -N; z < N; z++)
				if (x + y + z == 1000)
				{
					printf("x=%d y=%d z=%d\n", x, y, z);
				}
		}
	}
}