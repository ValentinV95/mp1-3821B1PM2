#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define N 150
float next(float pred, int i, float x){
	return pred * x / i;
}
float next_cos(float pred, int i, float x){
	return pred * x * x / (2 * i * (2 * i - 1));
}
float next_sin(float pred, int i, float x){
	return pred * x * x / (2 * i * (2 * i + 1));
}
float sum_in_order(float* arr, int len){
	float SUM = 0.0f;
	for (int i = 0; i < len; i++)
	{
		SUM += arr[i];
	}
	return SUM;
}
float sum_from_the_end(float* arr, int len){
	float SUM = 0.0f;
	for (int i = len - 1; i >= 0; i--)
	{
		SUM += arr[i];
	}
	return SUM;
}
float sum_in_pairs(float* arr, int len){
	float SUM = 0.0f, sum;
	for (int i = 1; i < len; i += 2)
	{
		sum = arr[i - 1] + arr[i];
		SUM += sum;
	}
	if (len % 2 == 1)
	{
		SUM += arr[len - 1];
	}
	return SUM;
}

int main()
{
	int func, sp;
	float* arr;
	float x, pred,value=0,true_value=0;
	printf("select the function:\n\t1 - sin(x)\n\t2 - cos(x)\n\t3 - exp^(x)\n\t4 - ln(1+x)\n");
	scanf_s("%d", &func);
	printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n");
	scanf_s("%d", &sp);
	printf("x = ");
	scanf_s("%f", &x);
	switch (func)
	{
	case 1://sin
		pred = x;
		arr = (float*)malloc(N * sizeof(float));
		arr[0] = x;
		for (int i = 1; i < N; i++)
		{
			pred = -next_sin(pred, i, x);
			arr[i] = pred;
		}
		if(func == 1) value = sum_in_order(arr, N);
		if (func == 2) value = sum_from_the_end(arr, N);
		if (func == 3) value = sum_in_pairs(arr, N);
		free(arr);
		printf("sin\n"); true_value = sinf(x);
		break;
	case 2://cos
		pred = 1;
		arr = (float*)malloc(N * sizeof(float));
		arr[0] = 1;
		for (int i = 1; i < N; i++)
		{
			pred = -next_cos(pred, i, x);
			arr[i] = pred;
		}
		if (func == 1) value = sum_in_order(arr, N);
		if (func == 2) value = sum_from_the_end(arr, N);
		if (func == 3) value = sum_in_pairs(arr, N);
		free(arr);
		printf("cos\n"); true_value = cosf(x);
		break;
	case 3://exp
		pred = 1;
		arr = (float*)malloc(N * sizeof(float));
		arr[0] = 1;
		for (int i = 1; i < N; i++)
		{
			pred = next(pred, i, x);
			arr[i] = pred;
		}
		if (func == 1) value = sum_in_order(arr, N);
		if (func == 2) value = sum_from_the_end(arr, N);
		if (func == 3) value = sum_in_pairs(arr, N);
		free(arr);
		printf("exp\n"); true_value = expf(x);
		break;
	case 4://ln
		pred = 1;
		arr = (float*)malloc(N * sizeof(float));
		int i = 1;
		pred = next(pred, i, x);
		arr[0] = 0;
		arr[1] = pred;
		for (i = 2; i < N; i++)
		{
			pred = -(i - 1) * next(pred, i, x);
			arr[i] = pred;
		}
		if (func == 1) value = sum_in_order(arr, N);
		if (func == 2) value = sum_from_the_end(arr, N);
		if (func == 3) value = sum_in_pairs(arr, N);
		free(arr);
		printf("ln\n"); true_value = logf(1+x);
		break;
	}
	printf("~ %.8f\n", value);
	printf("= %.8f\n", true_value);
	printf("absolute error = %.8f relative error = %.8f\n", fabsf(true_value - value), fabsf((true_value - value) / x));
	return 0;
}