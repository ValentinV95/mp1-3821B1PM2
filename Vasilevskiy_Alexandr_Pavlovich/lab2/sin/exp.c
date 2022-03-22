#include <math.h>
#include <stdio.h>
#include "next.h"

#define N 100 //elements in the Maclaurin series

double _1exp(double x)
{
	double EXP = 1, pred = 1;
	int i;
	for (i = 1; i < N; i++)
	{
		pred = next(pred, i, x);
		EXP += pred;
	}
	return EXP;
}

double _2exp(double x)
{
	double EXP = 0, pred = 1, a[N];
	int i;
	for (i = 1; i < N; i++)
	{
		pred = next(pred, i, x);
		a[i] = pred;
	}
	i--;
	for (; i > 0; i--)
	{
		EXP += a[i];
	}
	return 1+EXP;
}


double _3exp(double x)
{
	double EXP = 0, pred = 1, a1 = 0, a2 = 0, b = 0;
	int i, j = 0;
	for (i = 1; i < N; i++)
	{
		pred = next(pred, i, x);
		a2 = a1;
		a1 = pred;
		j++;
		if (j == 2)
		{
			b = a1 + a2;
			EXP += b;
			j = 0;
		}
	}
	if (j != 0)
	{
		b = a1 + a2;
		EXP += b;
	}
	return 1 + EXP;
}
FILE* fl;
void expchoose()
{
	double num = 0.0, _exp_ = 0.0, x, step,s[3];
	int sp = 0, print = 1, err;
	printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n\t4 - print\n");
	scanf_s("%d", &sp);
	printf("x = ");
	scanf_s("%lf", &num);
	switch (sp)
	{
	case 1:
		_exp_ = _1exp(num);
		break;
	case 2:
		_exp_ = _2exp(num);
		break;
	case 3:
		_exp_ = _3exp(num);
		break;
	case 4:
		print = 0;
		x = fabs(num);
		s[0] = s[1] = s[2] = 0;
		printf("step =");
		scanf_s("%lf", &step);
		printf("error:\n\t1 - absolute\n\t2 - relative\n");
		scanf_s("%d", &err);
		fopen_s(&fl,"table.txt","w+");
		step = fabs(step);
		if (err == 1)
		{
			for (num = -x; num < x; num += step)
			{
				fprintf_s(fl, "%.16lf\t%.16lf\t%.16lf\n", fabs(exp(num) - _1exp(num)), fabs(exp(num) - _2exp(num)), fabs(exp(num) - _3exp(num)));
				s[0] += fabs(exp(num) - _1exp(num));
				s[1] += fabs(exp(num) - _2exp(num));
				s[2] += fabs(exp(num) - _3exp(num));
			}
		}
		else if (err == 2)
		{
			for (num = -x; num < x; num += step)
			{
				fprintf_s(fl, "%.16lf\t%.16lf\t%.16lf\n", fabs((exp(num) - _1exp(num)) / num), fabs((exp(num) - _2exp(num)) / num), fabs((exp(num) - _3exp(num)) / num));
				s[0] += fabs((exp(num) - _1exp(num)) / num);
				s[1] += fabs((exp(num) - _2exp(num)) / num);
				s[2] += fabs((exp(num) - _3exp(num)) / num);
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
		printf("exp^(%lf)~%.16lf\n", num, _exp_);
		printf("exp^(%lf)=%.16lf\n", num, exp(num));
		printf("absolute error = %.16lf relative error = %.16lf\n", fabs(exp(num) - _exp_), fabs((exp(num) - _exp_) / num));
	}
}