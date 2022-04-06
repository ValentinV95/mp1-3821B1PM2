#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SummType(array, n) SimpleSumm(array,n);  
//#define SummType(array, n) ReverseSumm(array,n); 
//#define SummType(array, n) PairwiseSumm(array,n);  


float SinNext(float prev, float x, int i)
{
	i = 2 * i + 1;
	return (prev * (-1.f) * x * x) / (i * (i - 1.f));
}

float CosNext(float prev, float x, int i)
{
	i = 2 * i;
	return (prev * (-1.f) * x * x) / (i * (i - 1.f));
}

float ExpNext(float prev, float x, int i)
{
	return (prev * x) / ((float)i);
}

float LnNext(float prev, float x, int i)
{
	return (prev * (-1.f) * x * i) / (i + 1.f);
}

float SimpleSumm(float* array, int n)
{
	float summ = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		summ += array[i];
	}
	return summ;
}

float ReverseSumm(float* array, int n)
{
	float summ = 0;
	int i;

	for (i = 1; i <= n; i++)
	{
		summ += array[n - i];
	}
	return summ;
}

float PairwiseSumm(float* array, int n)
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

void CorrectCheck(float res, double(*original)(double x), double x)
{
	printf("\nAbsolute error is: %.8f", fabsf((float)original(x) - res));
	printf("\nRelative error is: %.8f %%", fabsf((((float)original(x) - res) / (float)original(x)) * 100.f));
}

void ArrayFill(float* array, int n, float(*res)(float, float, int), float param)
{
	int i;

	for (i = 1; i < n; i++)
	{
		array[i] = res(array[i - 1], param, i);
	}
}

void Menu(float* array, int n)
{
	enum function choice;
	double x;
	float summ = 0;
	enum function{SIN = 1, COS, EXP, LN};
	
	printf("Choose function:\n");
	printf("Enter:\n 1 for sin(x)\n 2 for cos(x)\n 3 for exp(x)\n 4 for ln(1+x)\n");
	scanf_s("%d", &choice);
	printf("Enter x:\n");
	scanf_s("%lf", &x);
	
	
	switch (choice)
	{
	case(SIN):

		array[0] = (float)x;
		ArrayFill(array, n, SinNext, x);
		summ = SummType(array,n);
		printf("\nsin(%.8f) = %.8f", x, summ);
		CorrectCheck(summ, sin, x);
		break;

	case(COS):

		array[0] = 1.f;
		ArrayFill(array, n, CosNext, x);
		summ = SummType(array,n);
		printf("\ncos(%lf) = %.16lf", x, summ);
		CorrectCheck(summ, cos, x);
		break;

	case(EXP):

		array[0] = 1.f;
		ArrayFill(array, n, ExpNext, x);
		summ = SummType(array,n);
		printf("\nexp(%lf) = %.16lf", x, summ);
		CorrectCheck(summ, exp, x);
		break;

	case(LN):

		array[0] = (float)x;
		ArrayFill(array, n, LnNext, x);
		summ = SummType(array,n);
		printf("\nln(1 + %lf) = %.16lf", x, summ);
		CorrectCheck(summ, log, x + 1);
		break;
	}
}

void main()
{
	float* array;
	int N = 100;

	array = (float*)malloc(N * sizeof(float));
	Menu(array, N);
}

