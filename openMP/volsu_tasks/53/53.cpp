#include <iostream>
#include <omp.h>
using namespace std;

int main(int argc, char const *argv[])
{
	long long target_sum = 10000000;
	int N = 1000;
	double tbegin = omp_get_wtime();
#pragma omp parallel shared(N, target_sum)
	{
#pragma omp for
		for (int x = -N; x < N; x++)
		{
			for (int y = -N; y < N; y++)
			{
				for (int z = -N; z < N; z++)
				{
					if (x * x + y * y * y + z * z * z * z == target_sum)
					{
						printf("%d^2+%d^3+%d^4=%d\n", x, y, z, target_sum);
					}
				}
			}
		}
	}
	double tend = omp_get_wtime();
	cout << "parallel " << tend - tbegin << "\n";
	tbegin = omp_get_wtime();
	for (int x = -N; x < N; x++)
	{
		for (int y = -N; y < N; y++)
		{
			for (int z = -N; z < N; z++)
			{
				if (x * x + y * y * y + z * z * z * z == target_sum)
				{
					printf("%d^2+%d^3+%d^4=%d\n", x, y, z, target_sum);
				}
			}
		}
	}
	tend = omp_get_wtime();
	cout << "classic " << tend - tbegin << "\n";
	return 0;
}
