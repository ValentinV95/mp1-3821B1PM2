#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define uint unsigned int

double summ(double function(double, double, uint), double x_sum, double first_summand)
{
	uint i;
	uint accuracy = 50;
	double sum = 0;
	double result = first_summand;

	for (i = 1; i < accuracy; i++)
	{
		sum += function(result, x_sum, i);
		result = function(result, x_sum, i);
	}

	return sum;
}

double sinx(double x_main, double x, uint i)
{
	return x_main * (-1 * x * x / ((2.0 * i) * (2.0 * i + 1.0)));
}

double cosx(double x_main, double x, uint i)
{
	return x_main * (-1 * x * x / ((2.0 * i) * (2.0 * i - 1.0)));
}

double expx(double x_main, double x, uint i)
{
	return x_main * (x / i);
}

double ln_1_plus_x(double x_main, double x, uint i)
{
	return x_main * (-1 * x * i / (i + 1.0));
}

double absolute_error(double built_in(double), double result, double x)
{
	return fabs(built_in(x) - result);
}

double relative_error(double built_in(double), double result, double x)
{
	return fabs((built_in(x) - result) / result) * 100; //%
}

void output(double built_in(double), double answer, double x)
{
	printf("\nFunction result: %.20lf", answer);
	printf("\nAbsolute error: %.20lf", absolute_error(built_in, answer, x));
	printf("\nRelative error: %.20lf%%", relative_error(built_in, answer, x));
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
		output(sin, summ(sinx, x, x) + x, x);
		break;

	case 2:
		output(cos, summ(cosx, x, 1) + 1, x);
		break;

	case 3:
		output(exp, summ(expx, x, 1) + 1, x);
		break;

	case 4:
		output(log, summ(ln_1_plus_x, x, x) + x, x + 1);
		break;

	default:
		printf("\nERROR: invalid function number");
		break;
	}

	return 0;
}
