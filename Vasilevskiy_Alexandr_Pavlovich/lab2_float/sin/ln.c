#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "next.h"

float* arr_ln(float x, int len)
{
	float* arr;
	float pred = 1;
	arr = (float*)malloc(len * sizeof(float));	
	if (arr)
	{
		int i = 1;
		pred = next(pred, i, x);
		arr[0] = 0;
		arr[1] = pred;
		for (i = 2; i < len; i++)
		{
			pred = -(i - 1) * next(pred, i, x);
			arr[i] = pred;
		}
	}
	return arr;
}

FILE *fl;
void lnchoose()
{
	float num = 0.0, _ln_ = 0.0,x,step,s[3], ln_order, ln_end, ln_pair;
	int sp = 0, print = 1, err;
	printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n\t4 - print\n");
	scanf_s("%d", &sp);
	printf("x = ");
	scanf_s("%f", &num);
	switch (sp)
	{
	case 1:
		_ln_ = sum_in_order(arr_ln(num, 150), 150);
		break;
	case 2:
		_ln_ = sum_from_the_end(arr_ln(num, 150), 150);
		break;
	case 3:
		_ln_ = sum_in_pairs(arr_ln(num, 150), 150);
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
				ln_order = sum_in_order(arr_ln(num, 150), 150);
				ln_end = sum_from_the_end(arr_ln(num, 150), 150);
				ln_pair = sum_in_pairs(arr_ln(num, 150), 150);
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf(logf(1 + num) - ln_order), fabsf(logf(1 + num) - ln_end), fabsf(logf(1 + num) - ln_pair));
				s[0] += fabsf(logf(1 + num) - ln_order);
				s[1] += fabsf(logf(1 + num) - ln_end);
				s[2] += fabsf(logf(1 + num) - ln_pair);
			}
		}
		else if (err == 2)
		{
			for (num = -x; num < x; num += step)
			{
				ln_order = sum_in_order(arr_ln(num, 150), 150);
				ln_end = sum_from_the_end(arr_ln(num, 150), 150);
				ln_pair = sum_in_pairs(arr_ln(num, 150), 150);
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf((logf(1 + num) - ln_order)/num), fabs((logf(1 + num) - ln_end) / num), fabsf((logf(1 + num) - ln_pair) / num));
				s[0] += fabsf((logf(1 + num) - ln_order) / num);
				s[1] += fabsf((logf(1 + num) - ln_end) / num);
				s[2] += fabsf((logf(1 + num) - ln_pair) / num);
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