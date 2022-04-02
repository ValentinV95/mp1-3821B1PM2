#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "next.h"

float* arr_sin(float x, int len)
{
	float* arr;
	float pred = x;
	arr = (float*)malloc(len * sizeof(float));
	if (arr)
	{
		arr[0] = x;
		for (int i = 1; i < len; i++)
		{
			pred = -next_sin(pred, i, x);
			arr[i] = pred;
		}
	}
	return arr;
}

FILE* fl;
void sinchoose()
{
	float num = 0.0, _sin_ = 0.0, x, step, s[3], sin_order, sin_end, sin_pair;
	int sp = 0, print = 1, err;
	printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n\t4 - print\n");
	scanf_s("%d", &sp);
	printf("x = ");
	scanf_s("%f", &num);
	switch (sp)
	{
	case 1:
		_sin_ = sum_in_order(arr_sin(num, 150), 150);
		break;
	case 2:
		_sin_ = sum_from_the_end(arr_sin(num, 150), 150);
		break;
	case 3:
		_sin_ = sum_in_pairs(arr_sin(num, 150), 150);
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
				sin_order = sum_in_order(arr_sin(num, 150), 150);
				sin_end = sum_from_the_end(arr_sin(num, 150), 150);
				sin_pair = sum_in_pairs(arr_sin(num, 150), 150);
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n", num, fabsf(sinf(num) - sin_order), fabsf(sinf(num) - sin_end), fabsf(sinf(num) - sin_pair));
				s[0] += fabsf(sinf(num) - sin_order);
				s[1] += fabsf(sinf(num) - sin_end);
				s[2] += fabsf(sinf(num) - sin_pair);
			}
		}
		else if (err == 2)
		{
			for (num = -x; num < x; num += step)
			{
				sin_order = sum_in_order(arr_sin(num, 150), 150);
				sin_end = sum_from_the_end(arr_sin(num, 150), 150);
				sin_pair = sum_in_pairs(arr_sin(num, 150), 150);
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n", num, fabsf((sinf(num) - sin_order) / num), fabsf((sinf(num) - sin_end) / num), fabsf((sinf(num) - sin_pair) / num));
				s[0] += fabsf((sinf(num) - sin_order) / num);
				s[1] += fabsf((sinf(num) - sin_end) / num);
				s[2] += fabsf((sinf(num) - sin_pair) / num);
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