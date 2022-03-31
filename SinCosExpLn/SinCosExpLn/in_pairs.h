#pragma once
double in_pairs_sin(double x)
{
	int z, i = 1;
	double* mas = malloc(100 * sizeof(double));
	mas[0] = x;
	double pair,res = 0, preds = x;
	while (i < 100)
	{
		z = 1;
		if (i % 2 != 0) z = -1;
		preds *= x * x / (2.0 * i + 1.0) / (2.0 * i);
		mas[i] = z * preds;
		i++;
	}
	for (i = 99; i > 0; i -= 2)
	{
		pair = mas[i] + mas[i - 1];
		res += pair;
	}
	free(mas);
	return res;
}

double in_pairs_cos(double x)
{
	int z, i = 1;
	double* mas = malloc(100 * sizeof(double));
	mas[0] = 1;
	double pair, res = 0, preds = 1;
	while (i < 100)
	{
		z = 1;
		if (i % 2 != 0) z = -1;
		preds *= x * x / (2.0 * i - 1.0) / (2.0 * i);
		mas[i] = z * preds;
		i++;
	}
	for (i = 99; i > 0; i -= 2)
	{
		pair = mas[i] + mas[i - 1];
		res += pair;
	}
	free(mas);
	return res;
}

double in_pairs_exp(double x)
{
	int i = 1;
	double* mas = malloc(100 * sizeof(double));
	mas[0] = 1;
	double pair, res = 0, preds = 1;
	while (i < 100)
	{
		preds *= x / (i + 0.0);
		mas[i] = preds;
		i++;
	}
	for (i = 99; i > 0; i -= 2)
	{
		pair = mas[i] + mas[i - 1];
		res += pair;
	}
	free(mas);
	return res;
}

double in_pairs_ln(double x)
{
	if (x >= 1 || x <= -1) return 0.0;
	int z, i = 1;
	double* mas = malloc(100 * sizeof(double));
	mas[0] = x;
	double pair, res = 0, preds = x;
	while (i < 100)
	{
		z = 1;
		if (i % 2 != 0) z = -1;
		preds *= i * x / (i + 1.0);
		mas[i] = z * preds;
		i++;
	}
	for (i = 99; i > 0; i -= 2)
	{
		pair = mas[i] + mas[i - 1];
		res += pair;
	}
	free(mas);
	return res;
}