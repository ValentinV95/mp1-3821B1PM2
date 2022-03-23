#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

typedef double(*function)(double, double, int);

double sinx(double y, double x, int i)
{
	return y * (-1 * x * x / ((2.0 * i) * (2.0 * i + 1.0)));
}

double cosx(double y, double x, int i)
{
	return y * (-1 * x * x / ((2.0 * i) * (2.0 * i - 1.0)));
}

double expx(double y, double x, int i)
{
	return y * (x / i);
}

double lnx(double y, double x, int i)
{
	return y * (-1 * x * i / (i + 1.0));
}

void create(double* array, int n, function r, double p)
{
	for (int i = 1; i < n; i++)
	{
		array[i] = r(array[i - 1], p, i);
	}
}

double straight(double* array, int n)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += array[i];
	}
	return sum;
}

double inverse(double* array, int n)
{
	double sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += array[n - i];
	}
	return sum;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	double x, r, sum = 0, obr;
	int select, n = 100;
	double* array = NULL;

	printf("What to calculate:\n1 - sine \n2 - cosine \n3 - exhibitor \n4 - natural logarithm от 1+х (-1<x<=1)\n");
	scanf_s("%d", &select);
	printf("Enter a number:");
	scanf_s("%lf", &x);

	array = (double*)malloc(n * sizeof(double));

	switch (select)
	{
	case(1):
	{
		array[0] = x;
		create(array, n, sinx, x);
		r = straight(array, n);
		obr = inverse(array, n);
		printf("Result: %.16lf\n", r);
		printf("Must be: %.16lf\n", sin(x));
		printf("Error rate: %.16lf\n", (sin(x) - r));
		printf("Reverse: %.16lf\n", obr);
		if (r < 0)
		{
			printf("Relative error: %.16lf%%\n", ((sin(x) - r) / r) * -100.0);
		}
		else
		{
			printf("Relative error: %.16lf%%\n", ((sin(x) - r) / r) * 100.0);
		}
		break;
	}
	case(2):
	{
		array[0] = 1;
		create(array, n, cosx, x);
		r = straight(array, n);
		obr = inverse(array, n);
		printf("Result: %.16lf\n", r);
		printf("Must be: %.16lf\n", cos(x));
		printf("Error rate: %.16lf\n", (cos(x) - r));
		printf("Reverse: %.16lf\n", obr);
		if (r < 0)
		{
			printf("Relative error: %.16lf%%\n", ((cos(x) - r) / r) * -100.0);
		}
		else
		{
			printf("Relative error: %.16lf%%\n", ((cos(x) - r) / r) * 100.0);
		}
		break;
	}
	case(3):
	{
		array[0] = 1;
		create(array, n, expx, x);
		r = straight(array, n);
		obr = inverse(array, n);
		printf("Result: %.16lf\n", r);
		printf("Must be: %.16lf\n", exp(x));
		printf("Error rate: %.16lf\n", (exp(x) - r));
		printf("Reverse: %.16lf\n", obr);
		printf("Relative error: %.16lf%%\n", ((exp(x) - r) / r) * 100.0);
		break;
	}
	case(4):
	{
		array[0] = x;
		create(array, n, lnx, x);
		r = straight(array, n);
		obr = inverse(array, n);
		printf("Result: %.16lf\n", r);
		printf("Must be: %.16lf\n", log(1 + x));
		printf("Errore rate: %.16lf\n", (log(1 + x) - r));
		printf("Reverse: %.16lf\n", obr);
		if (r < 0)
		{
			printf("Relative error: %.16lf%%\n", ((log(1 + x) - r) / r) * -100.0);
		}
		else
		{
			printf("Relative error: %.16lf%%\n", ((log(1 + x) - r) / r) * 100.0);
		}
		break;
	}
	}
}