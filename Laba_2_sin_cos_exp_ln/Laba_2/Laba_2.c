#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include<math.h>
#define amount_type revers_summ (arr,n);
typedef float(*option)(float, float, int);

float direct_summ(float* arr, int m)
{
	float summ = 0;
	int i;
	for (i = 0; i < m; i++)
	{
		summ += arr[i];
	}
	return summ;
}
float revers_summ(float* arr, int m)
{
	float summ = 0;
	int i;
	for (i = 1; i <= m; i++)
	{
		summ += arr[m - i];
	}
	return summ;
}
float paired_summ(float* arr, int m)
{
	int i;
	float summ = 0;
	for (i = 0; i < m - 1; i += 2)
		arr[i] += arr[i + 1];
	if (m % 2 == 1)
		summ += arr[i + 2];
	for (i = 0; i < m; i += 2)
		summ += arr[i];
	return summ;
}
float cos_1(float pred, float n, int i)
{
	i = 2 * i;
	return (pred * (-1.f) * n * n) / (i * (i - 1.f));
}
float sin_1(float pred, float n, int i)
{
	i = 2 * i + 1;
	return (pred * (-1.f) * n * n) / (i * (i - 1.f));
}
float ln_1(float pred, float n, int i)
{
	return (pred * (-1.f) * n * i) / (i + 1.f);
}
float exp_1(float pred, float n, int i)
{
	return (pred * n) / ((float)i);
}
void made_array(float* arr, int m, option result, float p)
{
	int i;

	for (i = 1; i < m; i++)
	{
		arr[i] = result(arr[i - 1], p, i);
	}
}

void main()
{
	float* arr;
	float x;
	int select;
	int n = 100;
	float summ = 0;
	setlocale(LC_ALL, "Rus");
	printf("Выберите функцию:\n");
	printf("1) косинус\n2) синус\n3) натуральный логарифм от (1+x)\n4) экспонента\n");
	scanf_s("%d", &select);
	printf("Введите x:\n");
	scanf_s("%f", &x);
	arr = (float*)malloc(n * sizeof(float));
	switch (select)
	{
	case(1):
	{
		arr[0] = 1.f;
		made_array(arr, n, cos_1, (float)x);
		summ = amount_type;
		printf("\ncos(x) = %.8f", summ);
		printf("\nЗначение из библиотеки: %f\n", (float)cos(x));
		printf("\nПогрешность: %.8f", (cos(x) - summ));
		printf("\nОтносительная погрешность в процентах: %.8f ", (((cos(x) - summ) / cos(x)) * 100));
		break;

	case(2):
		arr[0] = (float)x;
		made_array(arr, n, sin_1, (float)x);
		summ = amount_type;
		printf("\nsin(x) = %.8f", summ);
		printf("\nЗначение из библиотеки: %f\n", (float)sin(x));
		printf("\nПогрешность: %.8f", (sin(x) - summ));
		printf("\nОтносительная погрешность в процентах: %.8f ", (((sin(x) - summ) / sin(x)) * 100));
		break;

	case(3):
		arr[0] = (float)x;
		made_array(arr, n, ln_1, (float)x);
		summ = amount_type;
		printf("\nln(1+x) = %.8f", summ);
		printf("\nЗначение из библиотеки: %f\n", log(1.0 + x));
		printf("\nПогрешность: %.8f", (log(1.0 + x) - summ));
		printf("\nОтносительная погрешность в процентах: %.8f ", (((log(1.0 + x) - summ) / log(1.0 + x)) * 100));
		break;

	case(4):
		arr[0] = 1.f;
		made_array(arr, n, exp_1, (float)x);
		summ = amount_type;
		printf("\nexp(x) = %.8f", summ);
		printf("\nЗначение из библиотеки: %f\n", exp(x));
		printf("\nПогрешность: %.8f", (exp(x) - summ));
		printf("\nОтносительная погрешность в процентах: %.8f ", (((exp(x) - summ) / exp(x)) * 100));
		break;
	}
	default:
	{
		printf("Error");
		break;
	}
	}
}


