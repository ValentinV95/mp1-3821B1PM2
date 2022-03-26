#include <math.h>
#include <stdio.h>
#include "next.h"

#define N 150 //elements in the Maclaurin series

float _1exp(float x)
{
	float EXP = 1, pred = 1;
	int i;
	for (i = 1; i < N; i++)
	{
		pred = next(pred, i, x);
		EXP += pred;
	}
	return EXP;
}

float _2exp(float x)
{
	float EXP = 0, pred = 1, a[N];
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


float _3exp(float x)
{
	float EXP = 0, pred = 1, a1 = 0, a2 = 0, b = 0;
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
	float num = 0.0, _exp_ = 0.0, x, step,s[3];
	int sp = 0, print = 1, err;
	printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n\t4 - print\n");
	scanf_s("%d", &sp);
	printf("x = ");
	scanf_s("%f", &num);
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
		x = fabsf(num);
		s[0] = s[1] = s[2] = 0;
		printf("step =");
		scanf_s("%f", &step);
		printf("error:\n\t1 - absolute\n\t2 - relative\n");
		scanf_s("%d", &err);
		fopen_s(&fl,"table.txt","w+");
		fprintf_s(fl, "    Num: \t in order:\t the end:\t in pairs:\n");
		step = fabsf(step);
		if (err == 1)
		{
			for (num = -x; num < x; num += step)
			{
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf(expf(num) - _1exp(num)), fabsf(expf(num) - _2exp(num)), fabsf(expf(num) - _3exp(num)));
				s[0] += fabsf(expf(num) - _1exp(num));
				s[1] += fabsf(expf(num) - _2exp(num));
				s[2] += fabsf(expf(num) - _3exp(num));
			}
		}
		else if (err == 2)
		{
			for (num = -x; num < x; num += step)
			{
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf((expf(num) - _1exp(num)) / num), fabsf((expf(num) - _2exp(num)) / num), fabsf((expf(num) - _3exp(num)) / num));
				s[0] += fabsf((expf(num) - _1exp(num)) / num);
				s[1] += fabsf((expf(num) - _2exp(num)) / num);
				s[2] += fabsf((expf(num) - _3exp(num)) / num);
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
		printf("exp^(%f)~%.8f\n", num, _exp_);
		printf("exp^(%f)=%.8f\n", num, expf(num));
		printf("absolute error = %.8f relative error = %.8f\n", fabsf(expf(num) - _exp_), fabsf((expf(num) - _exp_) / num));
	}
}