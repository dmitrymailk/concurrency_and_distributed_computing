#include <omp.h>

void func()
{
#pragma omp parallel
	{
		for (int i = 0; i < 1000000; i++)
			;
	}
}

int main()
{
	// 	максимальное количество вложенных параллельных регионов
	omp_set_max_active_levels(2);

#pragma omp parallel
	{
		func();
		func();
		func();
		func();
	}

	return 0;
}