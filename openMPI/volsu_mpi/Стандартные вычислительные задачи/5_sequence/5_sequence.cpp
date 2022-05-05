#include <iostream>
#include <math.h>
using namespace std;

double InFunction(double x)
{ //Подынтегральная функция
	return sin(x);
}

double CalcIntegral(double a, double b, int n)
{
	double result = 0, h = (b - a) / n;

	for (int i = 0; i < n; i++)
	{
		result += InFunction(a + h * (i + 0.5));
	}

	result *= h;
	return result;
}

int main()
{
	double result = CalcIntegral(1, 10, 100000);
	cout << result << "\n";
	return 0;
}