#include <stdio.h>
#include <stdlib.h>
#include<math.h>

#define summ_type simple_summ(array,n);

typedef double(*function)(double, double, int);

double sin_next(double prev, double x, int i)
{
	i = 2 * i + 1;
	return (prev * (-1.0) * x * x) / (i * (i - 1.0));
}

double cos_next(double prev, double x, int i)
{
	i = 2 * i;
	return (prev * (-1.0) * x * x) / (i * (i - 1.0));
}

double exp_next(double prev, double x, int i)
{
	return (prev * x) / ((double)i);
}

double ln_next(double prev, double x, int i) 
{
	return (prev * (-1.0) * x * i) / (i + 1.0);
}

double simple_summ(double *array, int n)
{
	double summ = 0;
	int i;
	for (i=0; i<n; i++) 
	{
		summ += array[i];
	}
	return summ;
}

double inverse_summ(double* array, int n)
{
	double summ = 0;
	int i;
	for (i=1; i <= n; i++)
	{
		summ += array[n-i];
	}
	return summ;
}

double pairwise_summ(double* array, int n)
{
	int i, j;
	while (n > 1) 
	{
		for (i = 1, j = 0; i < n; i += 2, ++j) 
		{
			array[j] = array[i] + array[i - 1];
		}
		n /= 2;
	}
	return array[0];
}

void create_array(double *array, int n, function res, double param)
{
	int i;

	for (i = 1; i < n; i++)
	{
		array[i] = res(array[i - 1], param, i);
	}
}

void correct_check(double res, double(*original)(double x), double x) 
{
	printf("\nabsolute error is: %.16lf", fabs(original(x) - res));
	printf("\nrelative error is: %.16lf %%", fabs(((original(x) - res) / res))*100);
}

void main() 
{
	double *array = NULL;
	double x;
	int choose;
	int i,n = 100;   
	double summ = 0;

	printf("Choose function:\n");
	printf("Enter: 1 for sin(x), 2 for cos(x), 3 for exp(x), 4 for ln(1+x)\n");
	scanf_s("%d", &choose);
	printf("Enter x:\n");
	scanf_s("%lf", &x);

	array = (double*)malloc(n * sizeof(double));

	switch(choose)
	{	
	case(1):

		array[0] = x;
		create_array(array, n, sin_next, x);
		summ = summ_type;
		printf("\nsin(%.3lf) = %.16lf", x, summ);
		correct_check(summ, sin, x);
		break;

	case(2):

		array[0] = 1;
		create_array(array, n, cos_next, x);
		summ = summ_type;
		printf("\ncos(%lf) = %lf", x, summ);
		correct_check(summ, cos, x);
		break;

	case(3):

		array[0] = 1;
		create_array(array, n, exp_next, x);
		summ = summ_type;
		printf("\nexp(%lf) = %lf", x, summ);
		correct_check(summ, exp, x);
		break;

	case(4):

		array[0] = x;
		create_array(array, n, ln_next, x);
		summ = summ_type;
		printf("\nln(1 + %lf) = %lf", x, summ);
		correct_check(summ, log, x+1);
		break;
	}
}