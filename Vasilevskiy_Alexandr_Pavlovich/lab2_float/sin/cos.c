#include <math.h>
#include <stdio.h>
#include "next.h"

#define N 150 //elements in the Maclaurin series

float _1cos(float x)
{
	float COS = 1, pred = 1;
	int i;
	for (i = 1; i < N; i++)
	{
		pred = -next_cos(pred, i, x);
		COS += pred;
	}
	return COS;
}

float _2cos(float x)
{
	float COS = 0, pred = 1, a[N];
	int i;
	a[0] = 0;
	for (i = 1; i < N; i++)
	{
		a[i] = 0;
		pred = -next_cos(pred, i, x);
		a[i] = pred;
	}
	i--;
	for (; i > 0; i--)
	{
		COS += a[i];
	}
	return COS+1;
}

float _3cos(float x)
{
	float COS = 0, pred = 1, a1 = 0, a2 = 0, b = 0, pr1, pr2;
	int i, j = 0;
	for (i = 1; i < N; i += 2)
	{
		pred = -next_cos(pred, i, x);
		pr1 = pred;
		pred = -next_cos(pred, i + 1, x);
		pr2 = pred;
		COS += pr1 + pr2;
	}
	return COS + 1;
}

FILE* fl;
void coschoose()
{
	float num = 0.0, _cos_ = 0.0, x, step, s[3];
	int print = 1,sp = 0,err;
	printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n\t4 - print\n");
	scanf_s("%d", &sp);
	printf("x = ");
	scanf_s("%f", &num);
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
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf(cosf(num) - _1cos(num)), fabsf(cosf(num) - _2cos(num)), fabsf(cosf(num) - _3cos(num)));
				s[0] += fabsf(cosf(num) - _1cos(num));
				s[1] += fabsf(cosf(num) - _2cos(num));
				s[2] += fabsf(cosf(num) - _3cos(num));
			}
		}
		else if (err == 2)
		{
			for (num = -x; num < x; num += step)
			{
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf((cosf(num) - _1cos(num)) / num), fabsf((cosf(num) - _2cos(num)) / num), fabsf((cosf(num) - _3cos(num)) / num));
				s[0] += fabsf((cosf(num) - _1cos(num)) / num);
				s[1] += fabsf((cosf(num) - _2cos(num)) / num);
				s[2] += fabsf((cosf(num) - _3cos(num)) / num);
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
		printf("cos(%f)~%.8f\n", num, _cos_);
		printf("cos(%f)=%.8f\n", num, cosf(num));
		printf("absolute error = %.8f relative error = %.8f\n", fabsf(cosf(num) - _cos_), fabsf((cosf(num) - _cos_) / num));
	}
}