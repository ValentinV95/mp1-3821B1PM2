#include "stdlib.h"
#include "stdio.h"
#include "math.h"

// При x>1 или x<-1 ln(1+x) = 0

double* line_sin(double x)
{
	int z, i = 1;
	double* mas = malloc(100 * sizeof(double));
	mas[0] = x;
	double pair, res = 0, preds = x;
	while (i < 100)
	{
		z = 1;
		if (i % 2 != 0) z = -1;
		preds *= x * x / (2.0 * i + 1.0) / (2.0 * i);
		mas[i] = z * preds;
		i++;
	}
	return mas;
}

double* line_cos(double x)
{
	int z, i = 1;
	double* mas = malloc(100 * sizeof(double));
	mas[0] = 1;
	double res = 0, preds = 1;
	while (i < 100)
	{
		z = 1;
		if (i % 2 != 0) z = -1;
		preds *= x * x / (2.0 * i - 1.0) / (2.0 * i);
		mas[i] = z * preds;
		i++;
	}
	return mas;
}

double* line_exp(double x)
{
	int i = 1;
	double* mas = malloc(100 * sizeof(double));
	mas[0] = 1;
	double res = 0, preds = 1;
	while (i < 100)
	{
		preds *= x / (i + 0.0);
		mas[i] = preds;
		i++;
	}
	return mas;
}

double* line_ln(double x)
{
	int z, i = 1;
	double* mas = malloc(100 * sizeof(double));
	mas[0] = x;
	double pair, res = 0, preds = x;
	if (x >= 1 || x <= -1)
	{
		preds = 0;
		mas[0] = 0;
	}
	while (i < 100)
	{
		z = 1;
		if (i % 2 != 0) z = -1;
		preds *= i * x / (i + 1.0);
		mas[i] = z * preds;
		i++;
	}
	return mas;
}

double forward_sum(double* mas)
{
	int i;
	double res = 0;
	for (i = 0; i < 100; i++)
	{
		res += mas[i];
	}
	free(mas);
	return res;
}
double reverse_sum(double* mas)
{
	int i;
	double res = 0;
	for (i = 99; i >= 0; i--)
	{
		res += mas[i];
	}
	free(mas);
	return res;
}
double in_pair_sum(double* mas)
{
	int i;
	double pair, res = 0;
	for (i = 99; i > 0; i -= 2)
	{
		pair = mas[i] + mas[i - 1];
		res += pair;
	}
	free(mas);
	return res;
}

float error_sin(double sinx, double x)
{
	return fabs(sinx - sin(x));
}
float error_cos(double sinx, double x)
{
	return fabs(sinx - cos(x));
}
float error_exp(double sinx, double x)
{
	return fabs(sinx - exp(x));
}
float error_ln(double sinx, double x)
{
	return fabs(sinx - log(1 + x));
}




int main()
{
	int i;
	double x, res;
	printf("Input x: ");
	scanf_s("%lf", &x);
	printf("Input function you want to calculate:\n1)Sin(x)\n2)Cos(x)\n3)Exp(x)\n4)Ln(1+x)\n");
	scanf_s("%d", &i);
	if (i == 1)
	{
		printf("Input Method:\n1)Forward\n2)Reverse\n3)In pair\n");
		scanf_s("%d", &i);
		if (i == 1)
		{
			res = forward_sum(line_sin(x));
			printf("\n\nSinx Forward Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", sin(x));
			printf("error = %f\n", error_sin(res, x));
		}
		else if (i == 2)
		{
			res = reverse_sum(line_sin(x));
			printf("\n\nSinx Reverse Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", sin(x));
			printf("error = %f\n", error_sin(res, x));
		}
		else if (i == 3)
		{
			res = in_pair_sum(line_sin(x));
			printf("\n\nSinx In pair Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", sin(x));
			printf("error = %f\n", error_sin(res, x));
		}
	}
	else if (i == 2)
	{
		printf("Input Method:\n1)Forward\n2)Reverse\n3)In pair\n");
		scanf_s("%d", &i);
		if (i == 1)
		{
			res = forward_sum(line_cos(x));
			printf("\n\nCosx Forward Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", cos(x));
			printf("error = %f\n", error_cos(res, x));
		}
		else if (i == 2)
		{
			res = reverse_sum(line_cos(x));
			printf("\n\nCosx Reverse Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", cos(x));
			printf("error = %f\n", error_cos(res, x));
		}
		else if (i == 3)
		{
			res = in_pair_sum(line_cos(x));
			printf("\n\nCosx In pair Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", cos(x));
			printf("error = %f\n", error_cos(res, x));
		}
	}
	else if (i == 3)
	{
		printf("Input Method:\n1)Forward\n2)Reverse\n3)In pair\n");
		scanf_s("%d", &i);
		if (i == 1)
		{
			res = forward_sum(line_exp(x));
			printf("\n\nExpx Forward Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", exp(x));
			printf("error = %f\n", error_exp(res, x));
		}
		else if (i == 2)
		{
			res = reverse_sum(line_exp(x));
			printf("\n\nExpx Reverse Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", exp(x));
			printf("error = %f\n", error_exp(res, x));
		}
		else if (i == 3)
		{
			res = in_pair_sum(line_exp(x));
			printf("\n\nExpx In pair Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", exp(x));
			printf("error = %f\n", error_exp(res, x));
		}
	}
	else if (i == 4)
	{
		printf("Input Method:\n1)Forward\n2)Reverse\n3)In pair\n");
		scanf_s("%d", &i);
		if (i == 1)
		{
			res = forward_sum(line_ln(x));
			printf("\n\nln(1+x) Forward Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", log(1 + x));
			printf("error = %f\n", error_ln(res, x));
		}
		else if (i == 2)
		{
			res = reverse_sum(line_ln(x));
			printf("\n\nln(1+x) Reverse Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", log(1 + x));
			printf("error = %f\n", error_ln(res, x));
		}
		else if (i == 3)
		{
			res = in_pair_sum(line_ln(x));
			printf("\n\nln(1+x) In pair Mehtod\n");
			printf("my    = %lf\n", res);
			printf("real  = %lf\n", log(1 + x));
			printf("error = %f\n", error_ln(res, x));
		}
	}
}
