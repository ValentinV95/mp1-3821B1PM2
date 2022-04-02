#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "next.h"

float* arr_cos(float x, int len)
{
	float* arr;
	float pred = 1;
	arr = (float*)malloc(len * sizeof(float));
	if (arr)
	{
		arr[0] = 1;
		for (int i = 1; i < len; i++)
		{
			pred = -next_cos(pred, i, x);
			arr[i] = pred;
		}
	}
	return arr;
}

FILE* fl;
void coschoose()
{
	float num = 0.0, _cos_ = 0.0, x, step, s[3],cos_order,cos_end,cos_pair;
	int print = 1,sp = 0,err;
	printf("choose the summation method:\n\t1 - summation in order\n\t2 - summing from the end with an array\n\t3 - summation in pairs\n\t4 - print\n");
	scanf_s("%d", &sp);
	printf("x = ");
	scanf_s("%f", &num);
	switch (sp)
	{
	case 1:
		_cos_ = sum_in_order(arr_cos(num, 150), 150);
		break;
	case 2:
		_cos_ = sum_from_the_end(arr_cos(num, 150), 150);
		break;
	case 3:
		_cos_ = sum_in_pairs(arr_cos(num, 150), 150);
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
				cos_order = sum_in_order(arr_cos(num, 150), 150);
				cos_end = sum_from_the_end(arr_cos(num, 150), 150);
				cos_pair = sum_in_pairs(arr_cos(num, 150), 150);
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf(cosf(num) - cos_order), fabsf(cosf(num) - cos_end), fabsf(cosf(num) - cos_pair));
				s[0] += fabsf(cosf(num) - cos_order);
				s[1] += fabsf(cosf(num) - cos_end);
				s[2] += fabsf(cosf(num) - cos_pair);
			}
		}
		else if (err == 2)
		{
			for (num = -x; num < x; num += step)
			{
				cos_order = sum_in_order(arr_cos(num, 150), 150);
				cos_end = sum_from_the_end(arr_cos(num, 150), 150);
				cos_pair = sum_in_pairs(arr_cos(num, 150), 150);
				fprintf_s(fl, "%.8f\t%.8f\t%.8f\t%.8f\n",num, fabsf((cosf(num) - cos_order) / num), fabsf((cosf(num) - cos_end) / num), fabsf((cosf(num) - cos_pair) / num));
				s[0] += fabsf((cosf(num) - cos_order) / num);
				s[1] += fabsf((cosf(num) - cos_end) / num);
				s[2] += fabsf((cosf(num) - cos_pair) / num);
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