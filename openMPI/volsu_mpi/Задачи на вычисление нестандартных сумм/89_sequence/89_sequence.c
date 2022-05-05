#include <stdio.h>

int main()
{
	int N = 1790;
	int M = 230;

	double result = 0.0;

	for(int i=1; i<N; i++)
	{
		for(int j=1; j<M; j++)
		{
			result += (double)(1/((double)(i*i) + (double)(j*j*j)));
			
		}
	}

	printf("result sum = %f\n", result);
	// 2.854220
}