#include <iostream>
#include <omp.h>

void print_matrix(double **MATRIX, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << MATRIX[i][j] << " ";
		}

		std::cout << "\n";
	}
}

void fill_matrix(double **MATRIX, double num, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			MATRIX[i][j] = num;
		}
}

int equal(double **MATRIX_1, double **MATRIX_2, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (MATRIX_1[i][j] != MATRIX_2[i][j])
			{
				std::cout << "false\n";
				return 1;
			}
		}

	std::cout << "true\n";
	return 0;
}

void allocate_array(double **MATRIX, int size)
{
	for (int i = 0; i < size; i++)
		MATRIX[i] = new double[size];
}

int main(int argc, const char **argv)
{
	int size = 1000;
	double **MATRIX_A = new double *[size];
	double **MATRIX_B = new double *[size];
	double **MATRIX_C = new double *[size];

	allocate_array(MATRIX_A, size);
	allocate_array(MATRIX_B, size);
	allocate_array(MATRIX_C, size);

	fill_matrix(MATRIX_A, 1, size);
	fill_matrix(MATRIX_B, 1, size);

	double tbegin = omp_get_wtime();
	// последовательное
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++)
				MATRIX_C[i][j] += MATRIX_A[i][k] * MATRIX_B[k][j];
	double tend = omp_get_wtime();
	std::cout << "standart " << tend - tbegin << "\n";

	double **MATRIX_D = new double *[size];
	allocate_array(MATRIX_D, size);

	tbegin = omp_get_wtime();

// параллельное 1
#pragma omp parallel for shared(MATRIX_D, MATRIX_A, MATRIX_B)
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++)
				MATRIX_D[i][j] += MATRIX_A[i][k] * MATRIX_B[k][j];
	tend = omp_get_wtime();
	std::cout << "parallel_1 " << tend - tbegin << "\n";
	equal(MATRIX_C, MATRIX_D, size);

	double **MATRIX_E = new double *[size];
	allocate_array(MATRIX_E, size);
	tbegin = omp_get_wtime();

// параллельное 2
#pragma omp parallel for shared(MATRIX_D, MATRIX_A, MATRIX_B) schedule(dynamic)
	for (int i = 0; i < size; i++)
#pragma omp parallel for schedule(dynamic)
		for (int j = 0; j < size; j++)
			for (int k = 0; k < size; k++)
				MATRIX_E[i][j] += MATRIX_A[i][k] * MATRIX_B[k][j];

	tend = omp_get_wtime();
	std::cout << "parallel_2 " << tend - tbegin << "\n";

	equal(MATRIX_C, MATRIX_E, size);
	return 0;
}