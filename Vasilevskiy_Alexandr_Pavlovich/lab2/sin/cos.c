#include <math.h>
#include <stdio.h>
#include "next.h"

#define N 100 //elements in the Maclaurin series

double _1cos(double x)
{
	double COS = 1, pred = 1;
	int i;
	for (i = 1; i < N; i++)
	{
		pred = next(pred, i, x);
		if (i % 2 == 0)
		{
			pred = -pred;
			COS += pred;
		}
	}
	return COS;
}

double _2cos(double x)
{
	double COS = 0, pred = 1, a[N];
	int i;
	a[0] = 0;
	for (i = 1; i < N; i++)
	{
		a[i] = 0;
		pred = next(pred, i, x);
		if (i % 2 == 0)
		{
			pred = -pred;
			a[i] += pred;
		}
	}
	i--;
	for (; i > 0; i--)
	{
		COS += a[i];
	}
	return COS+1;
}

double _3cos(double x)
{
	double COS = 0, pred = 1, a1 = 0, a2 = 0, b = 0;
	int i, j = 0;
	for (i = 1; i < N; i++)
	{
		pred = next(pred, i, x);
		if (i % 2 == 0)
		{

			pred = -pred;
			a2 = a1;
			a1 = pred;
			j++;
			if (j == 2)
			{
				b = a1 + a2;
				COS += b;
				a1 = 0; a2 = 0; j = 0;
			}
		}
	}
	if (j != 0)
	{
		b = a1 + a2;
		COS += b;
	}
	return COS+1;
}

FILE* fl;
void coschoose()
{
	double num = 0.0, _cos_ = 0.0, x, step, s[3];
	int print = 1,sp = 0,err;
	printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n\t4 - print\n");
	scanf_s("%d", &sp);
	printf("x = ");
	scanf_s("%lf", &num);
	switch (sp)
	{
	case 1:
		_cos_ = _1cos(num);

		break;
	case 2:
		_cos_ = _2cos(num);
		break;
	case 3:
		_cos_ = _3cos(num);
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
				fprintf_s(fl, "%.16lf\t%.16lf\t%.16lf\n", fabs(cos(num) - _1cos(num)), fabs(cos(num) - _2cos(num)), fabs(cos(num) - _3cos(num)));
				s[0] += fabs(cos(num) - _1cos(num));
				s[1] += fabs(cos(num) - _2cos(num));
				s[2] += fabs(cos(num) - _3cos(num));
			}
		}
		else if (err == 2)
		{
			for (num = -x; num < x; num += step)
			{
				fprintf_s(fl, "%.16lf\t%.16lf\t%.16lf\n", fabs((cos(num) - _1cos(num)) / num), fabs((cos(num) - _2cos(num)) / num), fabs((cos(num) - _3cos(num)) / num));
				s[0] += fabs((cos(num) - _1cos(num)) / num);
				s[1] += fabs((cos(num) - _2cos(num)) / num);
				s[2] += fabs((cos(num) - _3cos(num)) / num);
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
		printf("cos(%lf)~%.16lf\n", num, _cos_);
		printf("cos(%lf)=%.16lf\n", num, cos(num));
		printf("absolute error = %.16lf relative error = %.16lf\n", fabs(cos(num) - _cos_), fabs((cos(num) - _cos_) / num));
	}
}