#include <omp.h>
#include <unistd.h>
#include <iostream>
#include <list>

/**
 * This example simulates the processing of a STL list (named lst in the code) in parallel through the
 * OpenMP task constructs (using the #pragma omp task directive). The example creates/instantiates
 * one OpenMP task for each element in lst and the OpenMP threads execute the tasks as soon as
 * they're ready to run.
 */

static void processElement(unsigned n)
{
// Tell who am I. The #pragma omp critical ensures that
// only one thread sends data to std::cout
#pragma omp critical
	std::cout << "Thread " << omp_get_thread_num() << " processing element " << n
			  << std::endl;
	// Simulate some work
	usleep(n * 1000);
}
int main(void)
{
	std::list<int> lst;
	// Fill the list
	for (int i = 0; i < 16; i++)
		lst.push_back(1 + i);

// Now process each element of the list in parallel
#pragma omp parallel // Create a parallel region
#pragma omp single	 // Only one thread will instantiate tasks
	{
		for (auto element : lst)
		{

#pragma omp task firstprivate(element)
			processElement(element);
		}
// Wait for all tasks to be finished
#pragma omp taskwait
	}
	return 0;
}
