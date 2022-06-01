#include <stdio.h>
#include <stdlib.h>
#include<math.h>

#define summType(nums,n) standartSumm(nums,n);
//#define summType(nums,n) inverseSumm(nums,n);
//#define summType(nums,n) pairwiseSumm(nums,n);

typedef float(*function)(float, float, int);

enum allFunctions {
	sin_x = 1, cos_x, exp_x, ln_x
};
enum allFunctions your;

void createNums(float* nums, int n, function data, float param)
{
	int i;

	for (i = 1; i < n; ++i)
	{
		nums[i] = data(nums[i - 1], param, i);
	}
}

float standartSumm(float* nums, int n) {
	float summ = 0;
	int i;
	for (i = 0; i < n; ++i) {
		summ += nums[i];
	}
	return summ;
}

float inverseSumm(float* nums, int n) {
	float summ = 0;
	int i;
	for (i = 1; i <= n; ++i)
	{
		summ += nums[n - i];
	}
	return summ;
}

float pairwiseSumm(float* nums, int n) {
	int i, j;
	while (n > 1)
	{
		for (i = 1, j = 0; i < n; i += 2, ++j)
		{
			nums[j] = nums[i] + nums[i - 1];
		}
		n /= 2;
	}
	return nums[0];
}

float sinNext(float previous, float x, int i) {
	i = 2 * i + 1;
	return (previous * (-1.0) * x * x) / (i * (i - 1.0));
}

float cosNext(float previous, float x, int i) {
	i = 2 * i;
	return (previous * (-1.0) * x * x) / (i * (i - 1.0));
}

float expNext(float previous, float x, int i) {
	return (previous * x) / ((float)i);
}

float lnNext(float previous, float x, int i) {
	return (previous * (-1.0) * x * i) / (i + 1.0);
}

void check(float data, float(*original)(float x), float x) {
	printf("\nrelative error: %f %%", fabs(((original(x) - data) / data)) * 100);
	printf("\nabsolute error: %f", fabs(original(x) - data));
}

void main() {
	float* nums = NULL;
	int n = 1000;
	float x, summ = 0;
	enum your choice;

	nums = (float*)malloc(n * sizeof(float));

	printf("Choose f(x)\n");
	printf("Enter:\n\t1 for sin(x)\n\t2 for cos(x)\n\t3 for exp(x)\n\t4 for ln(1+x)\n");
	scanf_s("%d", &choice);
	printf("Enter x value:\n");
	scanf_s("%f", &x);

	switch (choice) {
	case(sin_x):
		nums[0] = x;
		createNums(nums, n, sinNext, x);
		summ = summType(nums, n);
		printf("\nsin(%f) = %f", x, summ);
		check(summ, sinf, x);
		break;

	case(cos_x):
		nums[0] = 1;
		createNums(nums, n, cosNext, x);
		summ = summType(nums, n);
		printf("\ncos(%f) = %f", x, summ);
		check(summ, cosf, x);
		break;

	case(exp_x):
		nums[0] = 1;
		createNums(nums, n, expNext, x);
		summ = summType(nums, n);
		printf("\nexp(%lf) = %lf", x, summ);
		check(summ, expf, x);
		break;

	case(ln_x):
		nums[0] = x;
		createNums(nums, n, lnNext, x);
		summ = summType(nums, n);
		printf("\nln(1 + %f) = %f", x, summ);
		check(summ, logf, x + 1);
		break;

	}
	free(nums);
}
