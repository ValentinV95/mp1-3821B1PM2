#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define uint unsigned int
#define accuracy 50

double straight_summ(double function(double, uint), double x_sum, double first_summand)
{
	uint i;
	double sum = 0;
	double result = first_summand;

	for (i = 1; i < accuracy; i++)
	{
		sum += result;
		result *= function(x_sum, i);
	}

	return sum;
}

double reverse_summ(double function(double, uint), double x_sum, double first_summand)
{
	uint i;
	double sum = 0;
	double result = first_summand;

	for (i = 1; i < accuracy; i++)
	{
		result *= function(x_sum, i);
	}

	if (x_sum != 0)
	{
		for (i = accuracy - 1; i > 0; i--)
		{
			sum += result;
			result /= function(x_sum, i);
		}
	}
	sum += first_summand;

	return sum;
}

double sinx(double x, uint i)
{
	return -1 * x * x / ((2.0 * i) * (2.0 * i + 1.0));
}

double cosx(double x, uint i)
{
	return -1 * x * x / ((2.0 * i) * (2.0 * i - 1.0));
}

double expx(double x, uint i)
{
	return x / i;
}

double ln_1_plus_x(double x, uint i)
{
	return -1 * x * i / (i + 1.0);
}

double absolute_error(double built_in(double), double result, double x)
{
	return fabs(built_in(x) - result);
}

double relative_error(double built_in(double), double result, double x)
{
	double variant = built_in(x);
	if (result == 0.0 && variant == 0.0)
		return 0;
	else if ((result == 0.0 && variant != 0.0) || (result != 0.0 && variant == 0.0))
		return 100;
	else
		return fabs((variant - result) / result) * 100;
}

void output(double built_in(double), double answer_1, double answer_2, double x)
{
	printf("\nFor straight sum:");
	printf("\nFunction result: %.16lf", answer_1);
	printf("\nAbsolute error: %.16lf", absolute_error(built_in, answer_1, x));
	printf("\nRelative error: %.16lf%%\n", relative_error(built_in, answer_1, x));

	printf("\nFor reverse sum:");
	printf("\nFunction result: %.16lf", answer_2);
	printf("\nAbsolute error: %.16lf", absolute_error(built_in, answer_2, x));
	printf("\nRelative error: %.16lf%%\n", relative_error(built_in, answer_2, x));
}

int main()
{
	unsigned char select;
	double x;

	printf("\nFunction selection: \n\n\
	1 - sin(x) \n\
	2 - cos(x) \n\
	3 - exp(x) \n\
	4 - ln(1 + x) \n\n Number: ");
	scanf_s("%hhd", &select);

	printf("\nThe value of x: ");
	scanf_s("%lf", &x);

	switch (select)
	{
	case 1:
		output(sin, straight_summ(sinx, x, x), reverse_summ(sinx, x, x), x);
		break;

	case 2:
		output(cos, straight_summ(cosx, x, 1), reverse_summ(cosx, x, 1), x);
		break;

	case 3:
		output(exp, straight_summ(expx, x, 1), reverse_summ(expx, x, 1), x);
		break;

	case 4:
		output(log, straight_summ(ln_1_plus_x, x, x), reverse_summ(ln_1_plus_x, x, x), x + 1);
		break;

	default:
		printf("\nERROR: invalid function number\n");
		break;
	}

	return 0;
}
