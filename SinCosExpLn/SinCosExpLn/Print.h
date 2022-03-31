#pragma once
#include "error.h"

void choose_sinx()
{
	int i = 0;
	printf("Choose the mehod to calculate sin(x):\n1)Forward\n2)Reverse\n3)In pairs\n\n\nChoose: ");
		scanf_s("%d", &i);
	printf("Now input x:\n\nx = ");
	double x;
	scanf_s("%lf", &x);
	if (i == 1)
	{
		printf("forward sin = %lf\n", forward_sin(x));
		printf("real sin = %lf\n", sin(x));
		printf("error sin = %.8f\n", error_forward_sin(x));
	}
	else if (i == 2)
	{
		printf("reverse sin = %lf\n", reverse_sin(x));
		printf("real sin = %lf\n", sin(x));
		printf("error sin = %.8f\n", error_reverse_sin(x));
	}
	else if (i == 3)
	{
		printf("in_pairs sin = %lf\n", in_pairs_sin(x));
		printf("real sin = %lf\n", sin(x));
		printf("error sin = %.8f\n", error_in_pairs_sin(x));
	}
}

void choose_cosx()
{
	int i = 0;
	double x;
	printf("Choose the mehod to calculate cos(x):\n1)Forward\n2)Reverse\n3)In pairs\n\n\nChoose: ");
		scanf_s("%d", &i);
	printf("Now input x:\n\nx = ");
	scanf_s("%lf", &x);
	if (i == 1)
	{
		printf("forward cos = %lf\n", forward_cos(x));
		printf("real cos = %lf\n", cos(x));
		printf("error cos = %.8f\n", error_forward_cos(x));
	}
	else if (i == 2)
	{
		printf("reverse cos = %lf\n", reverse_cos(x));
		printf("real cos = %lf\n", cos(x));
		printf("error cos = %.8f\n", error_reverse_cos(x));
	}
	else if (i == 3)
	{
		printf("in_pairs cos = %lf\n", in_pairs_cos(x));
		printf("real cos = %lf\n", cos(x));
		printf("error cos = %.8f\n", error_in_pairs_cos(x));
	}
}

void choose_expx()
{
	int i = 0;
	double x;
	printf("Choose the mehod to calculate exp(x):\n1)Forward\n2)Reverse\n3)In pairs\n\n\nChoose: ");
		scanf_s("%d", &i);
	printf("Now input x:\n\nx = ");
	scanf_s("%lf", &x);
	if (i == 1)
	{
		printf("forward exp = %lf\n", forward_exp(x));
		printf("real exp = %lf\n", exp(x));
		printf("error exp = %.8f\n", error_forward_exp(x));
	}
	else if (i == 2)
	{
		printf("reverse exp = %lf\n", reverse_exp(x));
		printf("real exp = %lf\n", exp(x));
		printf("error exp = %.8f\n", error_reverse_exp(x));
	}
	else if (i == 3)
	{
		printf("in_pairs exp = %lf\n", in_pairs_exp(x));
		printf("real exp = %lf\n", exp(x));
		printf("error exp = %.8f\n", error_in_pairs_exp(x));
	}
}

void choose_lnx()
{
	int i = 0;
	double x;
	printf("Choose the mehod to calculate ln(x):\n1)Forward\n2)Reverse\n3)In pairs\n\n\nChoose: ");
		scanf_s("%d", &i);
	printf("Now input x:\n\nx = ");
	scanf_s("%lf", &x);
	if (i == 1)
	{
		printf("forward ln = %lf\n", forward_ln(x));
		printf("real ln = %lf\n", log(1 + x));
		printf("error ln = %.8f\n", error_forward_ln(x));
	}
	else if (i == 2)
	{
		printf("reverse ln = %lf\n", reverse_ln(x));
		printf("real ln = %lf\n", log(1 + x));
		printf("error ln = %.8f\n", error_reverse_ln(x));
	}
	else if (i == 3)
	{
		printf("in_pairs ln = %lf\n", in_pairs_ln(x));
		printf("real ln = %lf\n", log(1 + x));
		printf("error ln = %.8f\n", error_in_pairs_ln(x));
	}
	
}


void Choose()
{
	int i = 0;
	printf("Choose the function:\n1)Sin(x)\n2)Cos(x)\n3)Exp(x)\n4)ln(1+x)\n\nChoose: ");
	scanf_s("%d",&i);
	if (i == 1)
		choose_sinx();
	else if (i == 2)
		choose_cosx();
	else if (i == 3)
		choose_expx();
	else if (i == 4)
		choose_lnx();
	
}

