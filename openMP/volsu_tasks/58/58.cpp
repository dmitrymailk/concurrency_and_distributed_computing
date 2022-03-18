#include <iostream>
#include <omp.h>
using namespace std;

int main(int argc, char const *argv[])
{
	double pi_2 = 1;
	long long iterations = 100000000;
	double tbegin = omp_get_wtime();
#pragma omp parallel for reduction(* \
								   : pi_2)
	for (long long n = 1; n < iterations; n++)
	{
		pi_2 *= (double)(4 * n * n) / (double)(4 * n * n - 1);
	}
	double tend = omp_get_wtime();
	cout << "parallel pi/2 = " << pi_2 << " time = " << tend - tbegin << "\n";

	tbegin = omp_get_wtime();
	pi_2 = 1;
	for (long long n = 1; n < iterations; n++)
	{
		pi_2 *= (double)(4 * n * n) / (double)(4 * n * n - 1);
	}
	tend = omp_get_wtime();
	cout << "classic pi/2 = " << pi_2 << " time = " << tend - tbegin << "\n";
}