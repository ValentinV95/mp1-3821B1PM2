#include <math.h>
#include <stdio.h>
#include "next.h"

#define N 150 //elements in the Maclaurin series

double _1sin(double x)
{
	double SIN = 0, pred = -1;
	int i;
	for (i = 1; i < N; i++)
	{
		pred = next(pred, i, x);
		if (i % 2 != 0)
		{
			pred = -pred;
			SIN += pred;
		}
	}
	return SIN;
}

double _2sin(double x)
{
	double SIN = 0, pred = -1, a[N];
	int i;
	a[0] = 0;
	for (i = 1; i < N; i++)
	{
		a[i] = 0;
		pred = next(pred, i, x);
		if (i % 2 != 0)
		{
			pred = -pred;
			a[i] = pred;
		}
	}
	for (i = N-1; i >0; i--)
	{
		SIN += a[i];
	}
	return SIN;
}

double _3sin(double x)
{
	double SIN = 0, pred = -1, a1 = 0, a2 = 0, b = 0;
	int i, j = 0;
	for (i = 1; i < N; i++)
	{
		pred = next(pred, i, x);
		if (i % 2 != 0)
		{
			pred = -pred;
			a2 = a1;
			a1= pred;
			j++;
			if (j == 2)
			{
				b = a1 + a2;
				SIN += b;
				a1 = 0; a2 = 0; j = 0;
			}
		}
	}
	if (j != 0)
	{
		b = a1 + a2;
		SIN += b;
	}
	return SIN;
}

FILE* fl;
void sinchoose()
{
	double num = 0.0, _sin_ = 0.0, x, step, s[3];
	int sp = 0, print = 1, err;
	printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n\t4 - print\n");
	scanf_s("%d", &sp);
	printf("x = ");
	scanf_s("%lf", &num);
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
		x = fabs(num);
		s[0] = s[1] = s[2] = 0;
		printf("step =");
		scanf_s("%lf", &step);
		printf("error:\n\t1 - absolute\n\t2 - relative\n");
		scanf_s("%d", &err);
		fopen_s(&fl, "table.txt", "w+");
		step = fabs(step);
		if (err == 1)
		{
			for (num = -x; num < x; num += step)
			{
				fprintf_s(fl, "%.16lf\t%.16lf\t%.16lf\n", fabs(sin(num) - _1sin(num)), fabs(sin(num) - _2sin(num)), fabs(sin(num) - _3sin(num)));
				s[0] += fabs(sin(num) - _1sin(num));
				s[1] += fabs(sin(num) - _2sin(num));
				s[2] += fabs(sin(num) - _3sin(num));
			}
		}
		else if (err == 2)
		{
			for (num = -x; num < x; num += step)
			{
				fprintf_s(fl, "%.16lf\t%.16lf\t%.16lf\n", fabs((sin(num) - _1sin(num)) / num), fabs((sin(num) - _2sin(num)) / num), fabs((sin(num) - _3sin(num)) / num));
				s[0] += fabs((sin(num) - _1sin(num)) / num);
				s[1] += fabs((sin(num) - _2sin(num)) / num);
				s[2] += fabs((sin(num) - _3sin(num)) / num);
			}
		}

		fprintf_s(fl, "%.16lf\t%.16lf\t%.16lf\n", s[0], s[1], s[2]);
		fclose(fl);
	default:
		print = 0;
		printf("----");
	}
	if (print)
	{
		printf("sin(%lf)~%.16lf\n", num, _sin_);
		printf("sin(%lf)=%.16lf\n", num, sin(num));
		printf("absolute error = %.16lf relative error = %.16lf\n", fabs(sin(num) - _sin_), fabs((sin(num) - _sin_) / num));
	}
}