#include <math.h>
#include <stdio.h>
#include "next.h"

#define N 150 //elements in the Maclaurin series

float _1ln(float x)
{
	float LN = 0, pred = -1;
	int i=1;
	pred = -next(pred, i, x);
	LN += pred;
	for (i = 2; i < N; i++)
	{
		pred = (1.0f - i) * next(pred, i, x);
		LN += pred;
	}
	return LN;
}

float _2ln(float x)
{
	float LN = 0, pred = -1, a[N];
	int i = 1;
	pred = -next(pred, i, x);
	a[1] = pred;
	for (i = 2; i < N; i++)
	{
		pred = (1.0f-i)*next(pred, i, x);
		a[i] = pred;
	}
	i--;
	for (; i > 0; i--)
	{
		LN += a[i];
	}
	return LN;
}

float _3ln(float x)
{
	float LN = 0, pred = -1, a1 = 0, a2 = 0, b = 0;
	int i=1,j=1;
	pred = -next(pred, i, x);
	a1 = pred;
	for (i = 2; i < N; i++)
	{
		pred = (1.0f-i)*next(pred, i, x);
		a2 = a1;
		a1 = pred;
		j++;
		if (j == 2)
		{
			b = a1 + a2;
			LN += b;
			a1 = 0; a2 = 0; j = 0;
		}
	}
	if (j != 0)
	{
		b = a1 + a2;
		LN += b;
	}
	return LN;
}

FILE *fl;
void lnchoose()
{
	float num = 0.0, _ln_ = 0.0,x,step,s[3];
	int sp = 0, print = 1, err;
	printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n\t4 - print\n");
	scanf_s("%d", &sp);
	printf("x = ");
	scanf_s("%f", &num);
	switch (sp)
	{
	case 1:
		_ln_ = _1ln(num);
		break;
	case 2:
		_ln_ = _2ln(num);
		break;
	case 3:
		_ln_ = _3ln(num);
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
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf(logf(1 + num) - _1ln(num)), fabsf(logf(1 + num) - _2ln(num)), fabsf(logf(1 + num) - _3ln(num)));
				s[0] += fabsf(logf(1 + num) - _1ln(num));
				s[1] += fabsf(logf(1 + num) - _2ln(num));
				s[2] += fabsf(logf(1 + num) - _3ln(num));
			}
		}
		else if (err == 2)
		{
			for (num = -x; num < x; num += step)
			{
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf((logf(1 + num) - _1ln(num))/num), fabs((logf(1 + num) - _2ln(num)) / num), fabsf((logf(1 + num) - _3ln(num)) / num));
				s[0] += fabsf((logf(1 + num) - _1ln(num)) / num);
				s[1] += fabsf((logf(1 + num) - _2ln(num)) / num);
				s[2] += fabsf((logf(1 + num) - _3ln(num)) / num);
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
		printf("ln(%f)~%.8f \n", 1.0 + num, _ln_);
		printf("ln(%f)=%.8f\n", 1.0 + num, logf(1 + num));
		printf("absolute error = %.8f relative error = %.8f\n", fabsf(_ln_ - logf(1 + num)), fabsf((_ln_ - logf(1 + num)) / num));
	}
}