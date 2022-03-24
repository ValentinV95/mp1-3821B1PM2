#include <stdio.h>
#include <stdlib.h>
#include<math.h>

#define summ_type pairwise_summ(array, n);

typedef float(*function)(float, float, int);

float sin_next(float prev, float x, int i)
{
	i = 2 * i + 1;
	return (prev * (-1.f) * x * x) / (i * (i - 1.f));
}

float cos_next(float prev, float x, int i)
{
	i = 2 * i;
	return (prev * (-1.f) * x * x) / (i * (i - 1.f));
}

float exp_next(float prev, float x, int i)
{
	return (prev * x) / ((float)i);
}

float ln_next(float prev, float x, int i)
{
	return (prev * (-1.f) * x * i) / (i + 1.f);
}

float simple_summ(float* array, int n)
{
	float summ = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		summ += array[i];
	}
	return summ;
}

float inverse_summ(float* array, int n)
{
	float summ = 0;
	int i;
	for (i = 1; i <= n; i++)
	{
		summ += array[n - i];
	}
	return summ;
}

float pairwise_summ(float* array, int n)
{
	int i;
	float summ = 0;

	for (i = 0; i < n - 1; i += 2)
		array[i] += array[i + 1];

	if (n % 2 == 1)
		summ += array[i + 2];

	for (i = 0; i < n; i += 2)
		summ += array[i];

	return summ;
}

void create_array(float* array, int n, function res, float param)
{
	int i;

	for (i = 1; i < n; i++)
	{
		array[i] = res(array[i - 1], param, i);
	}
}

void correct_check(float res, double(*original)(double x), double x)
{
	printf("\nabsolute error is: %.8f", fabsf((float)original(x) - res));
	printf("\nrelative error is: %.8f %%", fabsf((((float)original(x) - res) / (float)original(x)) * 100.f));
}

void main()
{
	float* array;
	double x;
	int choose;
	int n = 100;
	float summ = 0;

	printf("Choose function:\n");
	printf("Enter: 1 for sin(x), 2 for cos(x), 3 for exp(x), 4 for ln(1+x)\n");
	scanf_s("%d", &choose);
	printf("Enter x:\n");
	scanf_s("%lf", &x);

	array = (float*)malloc(n * sizeof(float));

	switch (choose)
	{
	case(1):

		array[0] = (float)x;
		create_array(array, n, sin_next,(float)x);
		summ = summ_type;
		printf("\nsin(%.3f) = %.8f", x, summ);
		correct_check(summ, sin, x);
		break;

	case(2):

		array[0] = 1.f;
		create_array(array, n, cos_next, (float)x);
		summ = summ_type;
		printf("\ncos(%.3f) = %.8f", x, summ);
		correct_check(summ, cos, x);
		break;

	case(3):

		array[0] = 1.f;
		create_array(array, n, exp_next,(float)x);
		summ = summ_type;
		printf("\nexp(%.3f) = %.8f", x, summ);
		correct_check(summ, exp, x);
		break;

	case(4):

		array[0] =(float)x;
		create_array(array, n, ln_next, (float)x);
		summ = summ_type;
		printf("\nln(1 + %.3f) = %.8f", x, summ);
		correct_check(summ, log, x + 1.0);
		break;
	}
}