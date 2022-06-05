#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define M 150

float Cos_next(float prev, int i, float x)
{
	return prev * x * x / (2 * i * (2 * i - 1));
}
float Sin_next(float prev, int i, float x)
{
	return prev * x * x / (2 * i * (2 * i + 1));
}
float Next_(float prev, int i, float x)
{
	return prev * x / i;
}
float SumInPairs(float* arr, int lenght)
{
	float SUM = 0.0f, sum;
	for (int i = 1; i < lenght; i += 2)
	{
		sum = arr[i - 1] + arr[i];
		SUM += sum;
	}
	if (lenght % 2 == 1)
		SUM += arr[lenght - 1];
	return SUM;
}
float SumFromTheEnd(float* arr, int lenght)
{
	float SUM = 0.0f;
	for (int i = lenght - 1; i >= 0; i--)
		SUM += arr[i];
	return SUM;
}
float SumInOrder(float* arr, int lenght)
{
	float SUM = 0.0f;
	for (int i = 0; i < lenght; i++)
		SUM += arr[i];
	return SUM;
}

void main()
{
	int choose, selection;
	float* arr;
	float x, prev, MyValue = 0, Value = 0;
	printf("Choose the function:\n1) Cos(x)\n2) Sin(x)\n3) Ln(1+x)\n4) Exp^(x)\n");
	scanf_s("%d", &choose);
	printf("Select the summation method:\n1) Summation in pairs\n2) Summation in order\n3) Summing from the end with an array\n");
	scanf_s("%d", &selection);
	printf("Enter an argument: ");
	scanf_s("%f", &x);
	switch (choose)
	{
	case 1:
		prev = 1;
		arr = (float*)malloc(M * sizeof(float));
		arr[0] = 1;
		for (int i = 1; i < M; i++)
		{
			prev = -Cos_next(prev, i, x);
			arr[i] = prev;
		}
		if (selection == 1) MyValue = SumInPairs(arr, M);
		if (selection == 2) MyValue = SumInOrder(arr, M);
		if (selection == 3) MyValue = SumFromTheEnd(arr, M);

		free(arr);
		printf("Cos\n"); Value = cosf(x);
		break;
	case 2:
		prev = x;
		arr = (float*)malloc(M * sizeof(float));
		arr[0] = x;
		for (int i = 1; i < M; i++)
		{
			prev = -Sin_next(prev, i, x);
			arr[i] = prev;
		}
		if (selection == 1) MyValue = SumInPairs(arr, M);
		if (selection == 2) MyValue = SumInOrder(arr, M);
		if (selection == 3) MyValue = SumFromTheEnd(arr, M);
		free(arr);
		printf("Sin\n"); Value = sinf(x);
		break;

	case 3:
		prev = 1;
		arr = (float*)malloc(M * sizeof(float));
		int i = 1;
		prev = Next_(prev, i, x);
		arr[0] = 0;
		arr[1] = prev;
		for (i = 2; i < M; i++)
		{
			prev = -(i - 1) * Next_(prev, i, x);
			arr[i] = prev;
		}
		if (selection == 1) MyValue = SumInPairs(arr, M);
		if (selection == 2) MyValue = SumInOrder(arr, M);
		if (selection == 3) MyValue = SumFromTheEnd(arr, M);
		free(arr);
		printf("Ln\n"); Value = logf(1 + x);
		break;

	case 4:
		prev = 1;
		arr = (float*)malloc(M * sizeof(float));
		arr[0] = 1;
		for (int i = 1; i < M; i++)
		{
			prev = Next_(prev, i, x);
			arr[i] = prev;
		}
		if (selection == 1) MyValue = SumInPairs(arr, M);
		if (selection == 2) MyValue = SumInOrder(arr, M);
		if (selection == 3) MyValue = SumFromTheEnd(arr, M);
		free(arr);
		printf("Exp\n"); Value = expf(x);
		break;
	}
	printf("Programm result: %.8f\n", MyValue);
	printf("Exactly result: %.8f\n", Value);
	printf("Absolute error = %.8f\nRelative error = %.8f\n", fabsf(Value - MyValue), fabsf((Value - MyValue) / x));
}