#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>

const float Pi = 3.1415926535f;

void nul_0(float* array, int size)
{
	int i;

	for (i = 0; i < size; i++)
		array[i] = 0.f;
}

long long int fct(int a)
{
	int i;
	long long result = 1;

	if (a == 0)
		return result;

	else
	{
		for (i = 1; i <= a; i++)
			result *= i;

		return result;
	}
}

float sum(float* array, int size)
{
	int i;
	float p = 0;

	for (i = 0; i < size; i++)
		p += array[i];

	return p;
}

float reverse_sum(float* array, int size)
{
	int i;
	float p = 0;

	for (i = size; i > -1; i--)
		p += array[i];

	return p;
}

float duo_sum(float* array, int size)
{
	float p = 0;
	float brray[5];
	int i, m = 0;

	for (i = 0; i < 10; i += 2)
	{
		brray[m] = array[i] + array[i + 1];
		m++;
	}

	for (i = 0; i < m; i++)
		p += brray[i];

	return p;
}

void error(float a, float b)
{
	float c = 0.f, d = 0.f;

	c = fabsf(a - b);
	d = fabsf(c / a) * 100;

	printf("Абсолютная погрешность:                      %.20f\n", c);
	printf("Относительная погрешность:                   %.20f%%\n\n", d);
}

void exponent(float a)
{
	int i;
	float sum1, sum2, lib;
	float array[20];

	nul_0(array, 20);

	for (i = 0; i < 20; i++)
		array[i] = powf(a, (float)i) / (float)fct(i);

	sum1 = sum(array, 20);
	sum2 = reverse_sum(array, 19);
	lib = expf(a);

	printf("\nЭкспонента из библиотеки:                    %.20f\n\n", lib);
	printf("Экспонента, прямое суммирование:             %.20f\n", sum1);
	error(lib, sum1);
	printf("Экспонента, обратное суммирование:           %.20f\n", sum2);
	error(lib, sum2);
}

void ln(float a)
{
	int i;
	float t = (a - 1) / (a + 1);
	float array[20];
	float sum1, sum2, lib;

	nul_0(array, 20);

	for (i = 1; i < 20; i += 2)
		array[i] = powf(t, (float)i) / (float)i;

	sum1 = 2 * sum(array, 20);
	sum2 = 2 * reverse_sum(array, 19);
	lib = logf(a);

	printf("\nНатуральный логарифм из библиотеки:          %.20f\n\n", lib);
	printf("Натуральный логарифм, прямое суммирование:   %.20f\n", sum1);
	error(lib, sum1);
	printf("Натуральный логарифм, обратное суммирование: %.20f\n", sum2);
	error(lib, sum2);
}

void sinus(float a)
{
	int i, m = 0;
	float array[20];
	float sum1, sum2, sum3, lib;

	nul_0(array, 20);

	for (i = 1; i < 21; i += 2)
	{
		array[m] = powf(-1, (float)m) * powf(a, (float)i) / (float)fct(i);
		m++;
	}

	sum1 = sum(array, 10);
	sum2 = reverse_sum(array, 9);
	sum3 = duo_sum(array, 10);
	lib = sinf(a);

	printf("\nСинус из библиотеки:                         %.20f\n\n", lib);
	printf("Синус, прямое суммирование:                  %.20f\n", sum1);
	error(lib, sum1);
	printf("Синус, обратное суммирование:                %.20f\n", sum2);
	error(lib, sum2);
	printf("Синус, парное суммирование:                  %.20f\n", sum3);
	error(lib, sum3);
}

void cosinus(float a)
{
	int i, m = 0;
	float array[20];
	float sum1, sum2, sum3, lib;

	nul_0(array, 20);

	for (i = 0; i < 19; i += 2)
	{
		array[m] = powf(-1, (float)m) * powf(a, (float)i) / fct(i);
		m++;
	}

	sum1 = sum(array, 10);
	sum2 = reverse_sum(array, 9);
	sum3 = duo_sum(array, 10);
	lib = cosf(a);

	printf("\nКосинус из библиотеки:                       %.20f\n\n", lib);
	printf("Косинус, прямое суммирование:                %.20f\n", sum1);
	error(lib, sum1);
	printf("Косинус, обратное суммирование:              %.20f\n", sum2);
	error(lib, sum2);
	printf("Косинус, парное суммирование:                %.20f\n", sum3);
	error(lib, sum3);
}

void warning(int status)
{
	if (status == 4)
	{
		printf("(Помните, логарифм не может быть от 0 или от отрицательного числа)");
	}
}

void main()
{
	int choice;
	float argument = 1.f;

	setlocale(LC_ALL, "Russian");

	while (1)
	{
		printf("Выберите функцию:\n1) Синус\n2) Косинус\n3) Экспонента\n4) Натуральный логарифм\n\nВаш выбор: ");
		scanf_s("%d", &choice);
		getchar();

		printf("Введите аргумент");
		warning(choice);
		printf(": ");
		scanf_s("%f", &argument);
		getchar();

		if ((choice == 4) && (argument <= 0))
		{
			printf("Логарифм не может быть от 0 или от отрицательного числа\n");
		}

		else
		{
			switch (choice) {
			case 1:
			{
				sinus(argument);
				break;
			}

			case 2:
			{
				cosinus(argument);
				break;
			}

			case 3:
			{
				exponent(argument);
				break;
			}

			case 4:
			{
				ln(argument);
				break;
			}

			default:
			{
				printf("Такой функции нет\n");
				break;
			}
			}
		}

		printf("Введите любой символ чтобы продолжить: ");
		getchar();
		printf("\n");
	}
}