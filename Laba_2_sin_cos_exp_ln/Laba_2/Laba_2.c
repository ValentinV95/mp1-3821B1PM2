#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include<math.h>
#define amount_type direct_summ (arr,n);
typedef double(*option)(double, double, int);

double direct_summ(double* arr, int m)
{
	double summ = 0;
	int i;
	for (i = 0; i < m; i++)
	{
		summ += arr[i];
	}
	return summ;
}
double revers_summ(double* arr, int m)
{
	double summ = 0;
	int i;
	for (i = 1; i <= m; i++)
	{
		summ += arr[m - i];
	}
	return summ;
}
double paired_summ(double* arr, int m)
{
	int i, j;
	while (m > 1)
	{
		for (i = 1, j = 0; i < m; i += 2, ++j)
		{
			arr[j] = arr[i] + arr[i - 1];
		}
		m /= 2;
	}
	return arr[0];
}
double cos_1(double pred, double n, int i)
{
	i = 2 * i;
	return (pred * (-1.0) * n * n) / (i * (i - 1.0));
}
double sin_1(double pred, double n, int i)
{
	i = 2 * i + 1;
	return (pred * (-1.0) * n * n) / (i * (i - 1.0));
}
double ln_1(double pred, double n, int i)
{
	return (pred * (-1.0) * n * i) / (i + 1.0);
}
double exp_1(double pred, double n, int i)
{
	return (pred * n) / ((double)i);
}
void made_array(double* arr, int m, option result, double p)
{
	int i;

	for (i = 1; i < m; i++)
	{
		arr[i] = result(arr[i - 1], p, i);
	}
}

int main()
{
	double* arr = NULL;
	double x;
	int select;
	int n = 100;
	double summ = 0;
	setlocale(LC_ALL, "Rus");
	printf("Выберите функцию:\n");
	printf("1) косинус\n2) синус\n3) натуральный логарифм от (1+x)\n4) экспонента\n");
	scanf_s("%d", &select);
	printf("Введите x:\n");
	scanf_s("%lf", &x);
	arr = (double*)malloc(n * sizeof(double));
	switch (select)
	{
	case(1):
	{
		arr[0] = 1;
		made_array(arr, n, cos_1, x);
		summ = amount_type;
		printf("\ncos(x) = %.15lf", summ);
		printf("\nЗначение из библиотеки: %lf\n", cos(x));
		printf("\nПогрешность: %.15lf", (cos(x) - summ));
		printf("\nОтносительная погрешность в процентах: %.15lf ", (((cos(x) - summ) / summ) * 100));
		break;

	case(2):
		arr[0] = x;
		made_array(arr, n, sin_1, x);
		summ = amount_type;
		printf("\nsin(x) = %.15lf", summ);
		printf("\nЗначение из библиотеки: %lf\n", sin(x));
		printf("\nПогрешность: %.15lf", (sin(x) - summ));
		printf("\nОтносительная погрешность в процентах: %.15lf ", (((sin(x) - summ) / summ) * 100));
		break;

	case(3):
		arr[0] = x;
		made_array(arr, n, ln_1, x);
		summ = amount_type;
		printf("\nln(1+x) = %.15lf", summ);
		printf("\nЗначение из библиотеки: %lf\n", log(1 + x));
		printf("\nПогрешность: %.15lf", (log(1 + x) - summ));
		printf("\nОтносительная погрешность в процентах: %.15lf ", (((log(1 + x) - summ) / summ) * 100));
		break;

	case(4):
		arr[0] = 1;
		made_array(arr, n, exp_1, x);
		summ = amount_type;
		printf("\nexp(x) = %.15lf", summ);
		printf("\nЗначение из библиотеки: %lf\n", exp(x));
		printf("\nПогрешность: %.15lf", (exp(x) - summ));
		printf("\nОтносительная погрешность в процентах: %.15lf ", (((exp(x) - summ) / summ) * 100));
		break;
	}
	default:
	{
		printf("Error");
		break;
	}
	}
}
