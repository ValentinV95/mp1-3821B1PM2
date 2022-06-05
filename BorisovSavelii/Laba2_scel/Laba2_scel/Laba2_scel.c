#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define uint unsigned int
#define accuracy 8

float straight_summ(float function(float, uint), float x_sum, float first_summand)
{
	uint i;
	float sum = 0.f;
	float result = first_summand;

	for (i = 1; i < accuracy + 1; i++)
	{
		sum += result;
		result *= function(x_sum, i);
	}
	return sum;
}

float reverse_summ(float function(float, uint), float x_sum, float first_summand)
{
	uint i;
	float sum = 0.f;
	float result = first_summand;

	for (i = 1; i < accuracy + 1; i++)
	{
		result *= function(x_sum, i);
	}

	if (x_sum != 0)
	{
		for (i = accuracy; i > 0; i--)
		{
			sum += result;
			result /= function(x_sum, i);
		}
	}
	sum += first_summand;

	return sum;
}

float pairwise_summ(float function(float, uint), float x_sum, float first_summand)
{
	uint i;
	float sum = 0.f;
	float result = first_summand;
	
	if (accuracy % 2 == 0)
	{
		result *= function(x_sum, 1);
		sum += (first_summand + result);
		i = 2;
	}
	else
	{
		sum += first_summand;
		i = 1;
	}

	for (i; i < accuracy - 1; i++)
	{
		result *= function(x_sum, i);
		i++;
		sum += (result + result * function(x_sum, i));
		result *= function(x_sum, i);
	}
	
	return sum;
}

float sinx(float x, uint i)
{
	return (-1.f * x * x) / ((2.f * i) * (2.f * i + 1.f));
}

float cosx(float x, uint i)
{
	return (-1.f * x * x) / ((2.f * i) * (2.f * i - 1.f));
}

float expx(float x, uint i)
{
	return x / i;
}

float ln_1_plus_x(float x, uint i)
{
	return (-1.f * x * i) / (i + 1.f);
}

float absolute_error(double built_in, float result)
{
	return fabs((float)built_in - result);
}

float relative_error(double built_in, float result)
{
	if (result == 0.f && built_in == 0.0)
		return 0;
	else if ((result == 0.f && built_in != 0.0) || (result != 0.f && built_in == 0.0))
		return 100;
	else
		return fabs(((float)built_in - result) / (float)built_in) * 100.f;
}

void output(double built_in, float answer_1, float answer_2, float answer_3)
{
	printf("\nFor straight sum:");
	printf("\nFunction result: %.8f", answer_1);
	printf("\nAbsolute error: %.8f", absolute_error(built_in, answer_1));
	printf("\nRelative error: %.8f%%\n", relative_error(built_in, answer_1));

	printf("\nFor reverse sum:");
	printf("\nFunction result: %.8f", answer_2);
	printf("\nAbsolute error: %.8f", absolute_error(built_in, answer_2));
	printf("\nRelative error: %.8f%%\n", relative_error(built_in, answer_2));

	printf("\nFor pairwise sum:");
	printf("\nFunction result: %.8f", answer_3);
	printf("\nAbsolute error: %.8f", absolute_error(built_in, answer_3));
	printf("\nRelative error: %.8f%%\n", relative_error(built_in, answer_3));
}

int main()
{
	unsigned char select;
	float x;

	printf("\nFunction selection: \n\n\
	1 - sin(x) \n\
	2 - cos(x) \n\
	3 - exp(x) \n\
	4 - ln(1 + x) \n\n Number: ");
	scanf_s("%hhd", &select);

	printf("\nThe value of x: ");
	scanf_s("%f", &x);

	switch (select)
	{
	case 1:
		output(sin(x), straight_summ(sinx, x, x), reverse_summ(sinx, x, x), pairwise_summ(sinx, x, x));
		break;

	case 2:
		output(cos(x), straight_summ(cosx, x, 1.f), reverse_summ(cosx, x, 1.f), pairwise_summ(cosx, x, 1.f));
		break;

	case 3:
		output(exp(x), straight_summ(expx, x, 1.f), reverse_summ(expx, x, 1.f), pairwise_summ(expx, x, 1.f));
		break;

	case 4:
		output(log(x + 1.0), straight_summ(ln_1_plus_x, x, x), reverse_summ(ln_1_plus_x, x, x), pairwise_summ(ln_1_plus_x, x, x));
		break;

	default:
		printf("\nERROR: invalid function number\n");
		break;
	}

	return 0;
}
