#include <omp.h>
#include <stdio.h>
#include <iostream>

double f(int num)
{
	return (double)num;
}
double g(int num)
{
	return (double)num;
}
double h(int num)
{
	return (double)num;
}

int main()
{
	double result, fresult, gresult, hresult;
#pragma omp parallel
	{
		int num = omp_get_thread_num();
		if (num == 0)
			fresult = f(num);
		else if (num == 1)
			gresult = g(num);
		else if (num == 2)
			hresult = h(num);
	}
	result = fresult + gresult + hresult;

	std::cout << result << "\n";
	return 0;
}