#include <math.h>
#include <stdio.h>
#include "next.h"

#define N 150 //elements in the Maclaurin series

float _1sin(float x)
{
	float SIN = x, pred = x;
	int i;
	for (i = 1; i < N; i++)
	{
		pred = -next_sin(pred, i, x);
		SIN += pred;
	}
	return SIN;
}

float _2sin(float x)
{
	float SIN = 0, pred = x, a[N];
	int i;
	a[0] = 0;
	for (i = 1; i < N; i++)
	{
		pred = -next_sin(pred, i, x);
		a[i] = pred;
	}
	for (i = N - 1; i > 0; i--)
	{
		SIN += a[i];
	}
	return SIN + x;
}

float _3sin(float x)
{
	float SIN = 0, pred = x, s1, s2;;
	int i, j = 0;
	for (i = 1; i < N; i += 2)
	{
		pred = -next_sin(pred, i, x);
		s1 = pred;
		pred = -next_sin(pred, i + 1, x);
		s2 = pred;
		SIN += s1 + s2;
	}
	return SIN + x;
}

FILE* fl;
void sinchoose()
{
	float num = 0.0, _sin_ = 0.0, x, step, s[3];
	int sp = 0, print = 1, err;
	printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n\t4 - print\n");
	scanf_s("%d", &sp);
	printf("x = ");
	scanf_s("%f", &num);
	switch (sp)
	{
	case 1:
		_sin_ = _1sin(num);
		break;
	case 2:
		_sin_ = _2sin(num);
		break;
	case 3:
		_sin_ = _3sin(num);
		break;
	case 4:
		print = 0;
		x = fabsf(num);
		s[0] = s[1] = s[2] = 0;
		printf("step =");
		scanf_s("%f", &step);
		printf("error:\n\t1 - absolute\n\t2 - relative\n");
		scanf_s("%d", &err);
		fopen_s(&fl, "table.txt", "w+");
		fprintf_s(fl, "    Num: \t in order:\t the end:\t in pairs:\n");
		step = fabsf(step);
		if (err == 1)
		{
			for (num = -x; num < x; num += step)
			{
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf(sinf(num) - _1sin(num)), fabsf(sinf(num) - _2sin(num)), fabsf(sinf(num) - _3sin(num)));
				s[0] += fabsf(sinf(num) - _1sin(num));
				s[1] += fabsf(sinf(num) - _2sin(num));
				s[2] += fabsf(sinf(num) - _3sin(num));
			}
		}
		else if (err == 2)
		{
			for (num = -x; num < x; num += step)
			{
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf((sinf(num) - _1sin(num)) / num), fabsf((sinf(num) - _2sin(num)) / num), fabsf((sinf(num) - _3sin(num)) / num));
				s[0] += fabsf((sinf(num) - _1sin(num)) / num);
				s[1] += fabsf((sinf(num) - _2sin(num)) / num);
				s[2] += fabsf((sinf(num) - _3sin(num)) / num);
			}
		}

		fprintf_s(fl, "   Sum:   \t%.8f\t%.8f\t%.8f\n", s[0], s[1], s[2]);
		fclose(fl);
	default:
		print = 0;
		printf("----");
	}
	if (print)
	{
		printf("sin(%f)~%.8f\n", num, _sin_);
		printf("sin(%f)=%.8f\n", num, sinf(num));
		printf("absolute error = %.8f relative error = %.8f\n", fabsf(sinf(num) - _sin_), fabsf((sinf(num) - _sin_) / num));
	}
}