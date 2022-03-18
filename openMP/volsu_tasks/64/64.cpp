#include <iostream>
#include <omp.h>
#include <math.h>
using namespace std;

int main(int argc, char const *argv[])
{
	double S = 0;
	double N = 10000;
	double tbegin = omp_get_wtime();
#pragma omp parallel for reduction(+ \
								   : S)
	for (double i = (double)1 / N; i < 1; i++)
	{
		for (long long j = -i; j < N; j++)
		{
			S += (cos(j) * sin(i)) / (double)(4 + i * i + j * j * j * j);
		}
	}
	double tend = omp_get_wtime();
	cout << "parallel S = " << S << " time = " << tend - tbegin << "\n";
}