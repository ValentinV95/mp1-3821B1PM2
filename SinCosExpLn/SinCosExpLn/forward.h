#pragma once
double forward_sin(double x)
{
	int z,i = 1;
	double res = x,preds = x;
	while (i < 100)
	{
		z = 1;
		if (i % 2 != 0) z = -1;
		preds *= x * x / (2.0 * i + 1.0) / (2.0 * i);
		res += z * preds;
		i++;
	}
	return res;
}
double forward_cos(double x)
{
	int z, i = 1;
	double res = 1.0, preds = 1.0;
	while (i < 100)
	{
		z = 1;
		if (i % 2 != 0) z = -1;
		preds *= x * x / (2.0 * i - 1.0) / (2.0 * i);
		res += z * preds;
		i++;
	}
	return res;
}
double forward_exp(double x)
{
	int i = 1;
	double res = 1.0, preds = 1.0;
	while (i < 100)
	{
		preds *= x / (i + 0.0);
		res +=preds;
		i++;
	}
	return res;
}
double forward_ln(double x)
{
	if (x >= 1 || x <= -1) return 0.0;
	int z,i = 1;
	double res = x, preds = x;
	while (i < 100)
	{
		z = 1;
		if (i % 2 != 0) z = -1;
		preds *= i*x / (i + 1.0);
		res += z*preds;
		i++;
	}
	return res;
}