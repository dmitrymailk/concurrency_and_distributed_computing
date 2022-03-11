#include <omp.h>
#include <iostream>

int main()
{
#pragma omp parallel
	{
		// this is executed by a team of threads
		std::cout << "print " << omp_get_thread_num() << "\n";
	}
	return 0;
}