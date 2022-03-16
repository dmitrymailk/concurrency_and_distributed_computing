// Решение СЛАУ методом простой итерации

// Ниже приведена тестовая программа решения СЛАУ,
// система уравнений формировалась, удовлетворяющая условию сходимости, с
// диагональным преобладанием.В этой программе есть функции обычного и
// параллельного(с использованием технологии OpenMP) решения СЛАУ
// методом простой итерации.

#include <iostream>
#include <math.h>
#include <time.h>
#include <omp.h>
using namespace std;
float form_jacobi(float **alf, float *x, float *x1, float *bet, int n)
{
	int i, j;
	float s, max;
	for (i = 0; i < n; i++)

	{
		s = 0;
		for (j = 0; j < n; j++)
			s += alf[i][j] * x[j];
		s += bet[i];
		if (i == 0)
			max = fabs(x[i] - s);
		else if (fabs(x[i] - s) > max)
			max = fabs(x[i] - s);
		x1[i] = s;
	}
	return max;
}
float form_jacobi_parallel(float **alf, float *x, float *x1, float *bet, int n)
{
	int i, j;
	float s, max;
#pragma omp parallel for shared(alf, bet, x, x1) private(i, j, s)
	for (i = 0; i < n; i++)

	{
		s = 0;
		for (j = 0; j < n; j++)
			s += alf[i][j] * x[j];
		s += bet[i];
		if (i == 0)
			max = fabs(x[i] - s);
		else if (fabs(x[i] - s) > max)
			max = fabs(x[i] - s);
		x1[i] = s;
	}
	return max;
}

//Функция, реализующая распараллеленный метод простой итерации (точность //вычислений eps)

int jacobi_parallel(float **a, float *b, float *x, int n, float eps)
{
	float **f, *h, **alf, *bet, *x1, *xx, s, s1, max;
	int i, j, k, kvo;
	float t1, t2;
	cout << "\n Распараллеленный метод Якоби" << endl;
	f = new float *[n];
	for (i = 0; i < n; i++)
		f[i] = new float[n];
	h = new float[n];
	alf = new float *[n];
	for (i = 0; i < n; i++)
		alf[i] = new float[n];
	bet = new float[n];
	x1 = new float[n];
	xx = new float[n];
	cout << "\n СТАРТ" << endl;

	// cout<<"\n Вектор h"<<endl;

#pragma omp parallel for private(i, j)
	for (i = 0; i < n; i++)

	{
		for (j = 0; j < n; j++)
			if (i == j)
				alf[i][j] = 0;
			else
				alf[i][j] = -a[i][j] / a[i][i];
		bet[i] = b[i] / a[i][i];
	}
	for (i = 0; i < n; i++)
		x1[i] = bet[i];
	kvo = 0;
	max = 5 * eps;
	cout << "\n Старт итерационного процесса" << endl;
	t1 = omp_get_wtime();
	while (max > eps)

	{

		for (i = 0; i < n; i++)
			x[i] = x1[i];
		max = form_jacobi_parallel(alf, x, x1, bet, n);
		kvo++;
	}
	t2 = omp_get_wtime();
	cout << "Время итерационного процесса" << t2 - t1 << endl;
	cout << "\nmax=" << max << "\tkvo=" << kvo << "\teps=" << eps << endl;
	return kvo;
}

//Функция, реализуящая обычный метод простой итерации (точность вычислений eps)

int jacobi(float **a, float *b, float *x, int n, float eps)
{
	float **f, *h, **alf, *bet, *x1, *xx, s, s1, max;
	int i, j, k, kvo;
	float t1, t2;
	cout << "\n Метод Якоби" << endl;
	f = new float *[n];
	for (i = 0; i < n; i++)
		f[i] = new float[n];
	h = new float[n];
	alf = new float *[n];
	for (i = 0; i < n; i++)
		alf[i] = new float[n];
	bet = new float[n];
	x1 = new float[n];
	xx = new float[n];
	cout << "\n СТАРТ" << endl;
	for (i = 0; i < n; bet[i] = b[i] / a[i][i], i++)
		for (j = 0; j < n; j++)
			if (i == j)
				alf[i][j] = 0;
			else
				alf[i][j] = -a[i][j] / a[i][i];
	for (i = 0; i < n; i++)
		x1[i] = bet[i];
	kvo = 0;
	max = 5 * eps;
	cout << "\n Старт итерационного процесса" << endl;
	t1 = omp_get_wtime();
	while (max > eps)

	{
		for (i = 0; i < n; i++)
			x[i] = x1[i];
		max = form_jacobi(alf, x, x1, bet, n);
		kvo++;
	}
	t2 = omp_get_wtime();
	cout << "Время итерационного процесса" << t2 - t1 << endl;
	cout << "\nmax=" << max << "\tkvo=" << kvo << "\teps=" << eps << endl;
	return kvo;
}
float form(float **alf, float *x, float *bet, int n)
{
	int i, j;
	float s, max;
	for (i = 0; i < n; i++)

	{
		s = 0;
		for (j = 0; j < n; j++)
			s += alf[i][j] * x[j];
		s += bet[i];
		if (i == 0)
			max = fabs(x[i] - s);
		else if (fabs(x[i] - s) > max)
			max = fabs(x[i] - s);
		x[i] = s;
	}
	return max;
}
float form_parallel(float **alf, float *x, float *bet, int n)
{
	int i, j;
	float s, max;
#pragma omp parallel for shared(alf, bet, x) private(i, j, s)
	for (i = 0; i < n; i++)

	{
		s = 0;
		for (j = 0; j < n; j++)
			s += alf[i][j] * x[j];
		s += bet[i];
		if (i == 0)
			max = fabs(x[i] - s);
		else if (fabs(x[i] - s) > max)
			max = fabs(x[i] - s);
		x[i] = s;
	}
	return max;
}
int main(int argc, char **argv)
{
	int result, i, j, N;
	float **a, *b, *x, s, t1parl, t2parl, t1posl, t2posl, ep;
	clock_t t1, t2;
	cout << "N=";
	// cin >> N;
	N = 1000;
	ep = 1e-6;
	a = new float *[N];
	for (i = 0; i < N; i++)
		a[i] = new float[N];
	b = new float[N];
	x = new float[N];
	cout << "Input Matrix A" << endl;
	for (i = 0; i < N; a[i][i] = 1, i++)
		for (j = 0; j < N; j++)
			if (i != j)
				a[i][j] = 0.1 / (i + j);
	for (i = 0; i < N; i++)
		b[i] = sin(i);
	cout << "Матрица A занимает" << N * N * sizeof(float) << "байт" << endl;
	cout << "Матрица A занимает" << N * N * sizeof(float) / 1024 / 1024 << "Мбайт" << endl;
	cout << "Массив B занимает" << N * sizeof(float) << "байт" << endl;
	cout << "Массив В занимает" << N * sizeof(float) / 1024 / 1024 << "Мбайт" << endl;
	cout << "МЕТОД ЯКОБИ, СТАРТ!!!\n";
	t1posl = omp_get_wtime();
	cout << jacobi(a, b, x, N, ep);
	t2posl = omp_get_wtime();
	cout << "\nВремя последовательного счёта методом Якоби=" << t2posl - t1posl << endl;
	cout << "\n Вектор X" << endl;
	cout << x[0] << "\t" << x[N / 2] << "\t" << x[N - 1];
	cout << endl;
	cout << "ПАРАЛЛЕЛЬНЫЙ МЕТОД ЯКОБИ, СТАРТ!!!\n";
	t1parl = omp_get_wtime();
	cout << jacobi_parallel(a, b, x, N, ep);
	t2parl = omp_get_wtime();
	cout << "\n Вектор X" << endl;
	cout << x[0] << "\t" << x[N / 2] << "\t" << x[N - 1];
	cout << endl;
	cout << "\nВремя параллельного счёта методом Якоби=" << t2parl - t1parl << endl;
	return 0;
}