#pragma once
double reverse_sinx(double x,double xc, int i)
{
	int z;
	z = 1;
	if (i % 2 != 0) z = -1;
	if (i > 100) return x;
	return z*x + reverse_sinx(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) + 1)), xc, i + 1);
}
double reverse_sin(double x)
{
	return reverse_sinx(x, x, 0);
}

double reverse_cosx(double x, double xc, int i)
{
	int z;
	z = 1;
	if (i % 2 != 0) z = -1;
	if (i > 100) return x;
	return z * x + reverse_cosx(x * xc * xc / ((2.0 * (i + 1.0)) * (2.0 * (i + 1.0) - 1)), xc, i + 1);
}
double reverse_cos(double x)
{
	return reverse_cosx(1, x, 0);
}

double reverse_expx(double x, double xc, int i)
{
	if (i > 100) return x;
	return x + reverse_expx(x * xc / (i + 1.0), xc, i + 1);
}
double reverse_exp(double x)
{
	return reverse_expx(1, x, 0);
}

double reverse_lnx(double x, double xc, int i)
{
	if (x >= 1 || x <= -1) return 0.0;
	int z;
	z = -1;
	if (i % 2 != 0) z = 1;
	if (i > 100) return x;
	return z * x + reverse_lnx(x * xc * i / (i + 1.0), xc, i + 1);
}
double reverse_ln(double x)
{
	return reverse_lnx(x, x, 1);
}