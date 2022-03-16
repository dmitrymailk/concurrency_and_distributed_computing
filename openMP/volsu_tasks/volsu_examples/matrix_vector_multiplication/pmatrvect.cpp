// #include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <omp.h>
#include <time.h>

// Function that converts numbers form LongInt type to double type
double LiToDouble(LARGE_INTEGER x)
{
	double result =
		((double)x.HighPart) * 4.294967296E9 + (double)((x).LowPart);
	return result;
}
// Function that gets the timestamp in seconds
double GetTime()
{
	LARGE_INTEGER lpFrequency, lpPerfomanceCount;
	QueryPerformanceFrequency(&lpFrequency);
	QueryPerformanceCounter(&lpPerfomanceCount);
	return LiToDouble(lpPerfomanceCount) / LiToDouble(lpFrequency);
}

// Function for simple definition of matrix and vector elements
void DummyDataInitialization(int *pMatrix, int *pVector, int Size)
{
	int i, j; // Loop variables
	for (i = 0; i < Size; i++)
	{
		pVector[i] = 1;
		for (j = 0; j < Size; j++)
			pMatrix[i * Size + j] = i;
	}
}

// Function for random definition of matrix and vector elements
void RandomDataInitialization(int *pMatrix, int *pVector, int Size)
{
	int i, j; // Loop variables
	srand(unsigned(clock()));
	for (i = 0; i < Size; i++)
	{
		pVector[i] = rand();
		for (j = 0; j < Size; j++)
			pMatrix[i * Size + j] = rand();
	}
}

// Function for memory allocation and definition of object�s elements
void ProcessInitialization(int *&pMatrix, int *&pVector, int *&pResult, int &Size)
{
	// Size of initial matrix and vector definition
	do
	{
		printf("\nEnter size of the initial objects: ");
		scanf("%d", &Size);
		printf("\nChosen objects size = %d\n", Size);
		if (Size <= 0)
			printf("\nSize of objects must be greater than 0!\n");
	}

	while (Size <= 0);
	// Memory allocation
	pMatrix = new int[Size * Size];
	pVector = new int[Size];
	pResult = new int[Size];
	// Definition of matrix and vector elements

	DummyDataInitialization(pMatrix, pVector, Size);
}

// Function for formatted matrix output
void PrintMatrix(int *pMatrix, int RowCount, int ColCount)
{
	int i, j; // Loop variables
	for (i = 0; i < RowCount; i++)
	{
		for (j = 0; j < ColCount; j++)
			printf("%7.4f ", pMatrix[i * RowCount + j]);
		printf("\n");
	}
}

// Function for formatted vector output
void PrintVector(int *pVector, int Size)
{
	int i;
	for (i = 0; i < Size; i++)
		printf("%7.4f ", pVector[i]);
}

// Function for serial matrix-vector multiplication
void SerialResultCalculation(int *pMatrix, int *pVector, int *pResult, int Size)
{
	int i, j; // Loop variables
	for (i = 0; i < Size; i++)
	{
		pResult[i] = 0;
		for (j = 0; j < Size; j++)
			pResult[i] += pMatrix[i * Size + j] * pVector[j];
	}
}

// Function for parallel matrix-vector multiplication
void ParallelResultCalculation(int *pMatrix, int *pVector, int *pResult, int Size)
{
	int i, j; // Loop variables
#pragma omp parallel for private(j)
	for (i = 0; i < Size; i++)
	{
		for (j = 0; j < Size; j++)
			pResult[i] += pMatrix[i * Size + j] * pVector[j];
	}
}

// Testing the result of parallel matrix-vector multiplication
void TestResult(int *pMatrix, int *pVector, int *pResult, int Size)
{
	// Buffer for storing the result of serial matrix-vector multiplication
	int *pSerialResult;
	int equal = 0; // Flag, that shows wheather the vectors are identical
	int i;		   // Loop variable
	pSerialResult = new int[Size];
	SerialResultCalculation(pMatrix, pVector, pSerialResult, Size);
	for (i = 0; i < Size; i++)
	{
		if (pResult[i] != pSerialResult[i])
			equal = 1;
	}

	if (equal == 1)
		printf("The results of serial and parallel algorithms are NOT identical. Check your code.");
	else
		printf("The results of serial and parallel algorithms are identical.");
	delete[] pSerialResult;
}

// Function for computational process termination
void ProcessTermination(int *pMatrix, int *pVector, int *pResult)
{
	delete[] pMatrix;
	delete[] pVector;
	delete[] pResult;
}

void main()
{
	int *pMatrix; // The first argument - initial matrix
	int *pVector; // The second argument - initial vector
	int *pResult; // Result vector for matrix-vector multiplication
	int Size;	  // Sizes of initial matrix and vector
	double Start, Finish, Duration;
	printf("Parallel matrix-vector multiplication program\n");
	// Memory allocation and definition of objects' elements
	ProcessInitialization(pMatrix, pVector, pResult, Size);
	// Matrix and vector output
	// printf ("Initial Matrix \n");
	// PrintMatrix(pMatrix, Size, Size);
	// printf("Initial Vector \n");
	// PrintVector(pVector, Size);
	// Matrix-vector multiplication
	Start = GetTime();
	ParallelResultCalculation(pMatrix, pVector, pResult, Size);
	Finish = GetTime();

	Duration = Finish - Start;
	TestResult(pMatrix, pVector, pResult, Size);
	// Printing the result vector
	printf("\n Result Vector: \n");
	// PrintVector(pResult, Size);
	//  Printing the time spent by matrix-vector multiplication
	printf("\n Time of execution: %f\n", Duration);
	// Computational process termination
	ProcessTermination(pMatrix, pVector, pResult);
}