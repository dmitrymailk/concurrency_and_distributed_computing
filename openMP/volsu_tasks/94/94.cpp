#include <iostream>
#include <omp.h>
#include <math.h>
using namespace std;

int main(int argc, char const *argv[])
{
	double S = 0;
	long long N = 10000;
	double tbegin = omp_get_wtime();
#pragma omp parallel for reduction(+ \
								   : S)
	for (long long i = 1; i < N; i++)
	{
		for (long long j = -i; j < N; j++)
		{
			S += (cos(j) * sin(i)) / (double)(4 + i * i + j * j * j * j);
		}
	}
	double tend = omp_get_wtime();
	cout << "parallel S = " << S << " time = " << tend - tbegin << "\n";

	tbegin = omp_get_wtime();
	S = 0;
	for (long long i = 1; i < N; i++)
	{
		for (long long j = -i; j < N; j++)
		{
			S += (double)(cos(j) * sin(i)) / (double)(4 + i * i + j * j * j * j);
		}
	}
	tend = omp_get_wtime();
	cout << "classic S = " << S << " time = " << tend - tbegin << "\n";
}