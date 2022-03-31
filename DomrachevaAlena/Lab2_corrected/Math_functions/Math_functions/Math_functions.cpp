#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

float sum_par(float *mas)
{
	int i, k;
	float arr[50];
	float res = 0.f;
	for (i = 0, k = 0; i < 50; i++, k += 2)
	{
		arr[i] = mas[k] + mas[k + 1];
	}
	for (i = 49; i >= 0; i--)
	{
		res += arr[i];
	}
	return res;
}

float sum_obr(float *mas)
{
	int i;
	float res = 0.f;
	for (i = 99; i >= 0; i--)
	{
		res += mas[i];
	}
	return res;
}

float sum_str(float *mas)
{
	int i;
	float res = 0.f;
	for (i = 0; i < 100; i++)
	{
		res += mas[i];
	}
	return res;
}

float exp_f(float* mas_exp, float x)
{
	float pred = 1.f, sled, n = 1.f;
	int i;
	mas_exp[0] = 1.f;
	for (i = 1; i < 100; i++)
	{
		sled = x / n;
		mas_exp[i] = (float)(pred * sled);
		pred *= sled;
		n += 1.f;
	}
	return *mas_exp;
}

float ln_f(float* mas_ln, float x)
{
	float pred = x, sled, n = 1.f;
	int i, k;
	mas_ln[0] = x;
	for (i = 1; i < 100; i++)
	{
		sled = x / (n + 1.f);
		mas_ln[i] = (float)(pow(-1.f, i) * pred * sled);
		pred *= x;
		n += 1.f;
	}
	return *mas_ln;
}

float cos_f(float* mas_cos, float x)
{
	const float PI = 3.14159265f;
	float a, sled, pred = 1.f, n = 1.f;
	int i;
	mas_cos[0] = 1.f;
	for (a = 2.f * PI; x < 0.f;)
	{
		x += a;
	}
	for (a = 2.f * PI; x > a;)
	{
		x -= a;
	}
	for (i = 1; i < 100; i++)
	{
		sled = (x * x) / (n * (n + 1.f));
		mas_cos[i] = (float)(pow(-1, i) * pred * sled);
		pred *= sled;
		n += 2.f;
	}
	return* mas_cos;
}

float sin_f(float* mas_sin, float x)
{
	const float PI = 3.14159265f;
	float a, sled,pred,n=1.f;
	int i;

	for (a = 2.f * PI; x < 0.f;)
	{
		x += a;
	}
	for (a = 2.f * PI; x > a;)
	{
		x -= a;
	}
	pred = x;
	mas_sin[0] = x;
	for (i = 1; i < 100; i++)
	{
		sled = (x * x) / ((n + 1.f) * (n + 2.f));
		mas_sin[i] = (float)(pow(-1.f, i) * pred * sled);
		pred *= sled;
		n += 2.f;
	}
	return *mas_sin;
}

int main()
{
	float x, y;
	float mas_sin[100], mas_cos[100], mas_ln[100], mas_exp[100];
	float sin_result, sin_math, sin_result_obr, sin_result_par, o_str_sin, o_obr_sin, o_par_sin;
	float cos_result, cos_math, cos_result_obr, cos_result_par, o_str_cos, o_obr_cos, o_par_cos;
	float ln_result, ln_math, ln_result_obr, ln_result_par, o_str_ln, o_obr_ln, o_par_ln;
	float exp_result, exp_math, exp_result_obr, exp_result_par, o_str_exp, o_obr_exp, o_par_exp;
	setlocale(LC_ALL, "Russian");
	printf("Введите x:\n");
	scanf_s("%f", &x);

	*mas_sin = sin_f(mas_sin, x);
	sin_result = sum_str(mas_sin);
	sin_result_obr = sum_obr(mas_sin);
	sin_result_par = sum_par(mas_sin);
	sin_math = sin(x);
	printf("sin_прямой = %f\n", sin_result);
	printf("sin_обратный = %f\n", sin_result_obr);
	printf("sin_попарный = %f\n", sin_result_par);
	printf("sin_math = %f\n", sin_math);
	o_str_sin = sin_result - sin_math;
	o_obr_sin = sin_result_obr - sin_math;
	o_par_sin = sin_result_par - sin_math;
	printf("Ошибка(прямой) = %f\n", o_str_sin);
	printf("Ошибка(обратный) = %f\n", o_obr_sin);
	printf("Ошибка(попарный) = %f\n\n", o_par_sin);
	
	*mas_cos = cos_f(mas_cos, x);
	cos_result = sum_str(mas_cos);
	cos_result_obr = sum_obr(mas_cos);
	cos_result_par = sum_par(mas_cos);
	cos_math = cos(x);	
	printf("cos_прямой = %f\n", cos_result);
	printf("cos_обратный = %f\n", cos_result_obr);
	printf("cos_попарный = %f\n", cos_result_par);
	printf("cos_math = %f\n", cos_math);
	o_str_cos = cos_result - cos_math;
	o_obr_cos = cos_result_obr - cos_math;
	o_par_cos = cos_result_par - cos_math;
	printf("Ошибка(прямой) = %f\n", o_str_cos);
	printf("Ошибка(обратный) = %f\n", o_obr_cos);
	printf("Ошибка(попарный) = %f\n\n", o_par_cos);


	if ((x > -1.f) && (x < 1.f))
	{
		y = 1.f + x;
		*mas_ln = ln_f(mas_ln, x);
		ln_result = sum_str(mas_ln);
		ln_result_obr = sum_obr(mas_ln);
		ln_result_par = sum_par(mas_ln);
		ln_math = log(y);
		printf("ln_прямой = %f\n", ln_result);
		printf("ln_обратный = %f\n", ln_result_obr);
		printf("ln_попарный = %f\n", ln_result_par);
		printf("ln_math = %f\n", ln_math);
		o_str_ln = ln_result - ln_math;
		o_obr_ln = ln_result_obr - ln_math;
		o_par_ln = ln_result_par - ln_math;
		printf("Ошибка(прямой) = %f\n", o_str_ln);
		printf("Ошибка(обратный) = %f\n", o_obr_ln);
		printf("Ошибка(попарный) = %f\n\n", o_par_ln);
	}
	else
	{
		printf("x не удовлетворяет области определения\n\n");
	}

	*mas_exp = exp_f(mas_exp, x);
	exp_result = sum_str(mas_exp);
	exp_result_obr = sum_obr(mas_exp);
	exp_result_par = sum_par(mas_exp);
	exp_math = exp(x);
	printf("exp_прямой = %f\n", exp_result);
	printf("exp_обратный = %f\n", exp_result_obr);
	printf("exp_попарный = %f\n", exp_result_par);
	printf("exp_math = %f\n", exp_math);
	o_str_exp = exp_result - exp_math;
	o_obr_exp = exp_result_obr - exp_math;
	o_par_exp = exp_result_par - exp_math;
	printf("Ошибка(прямой) = %f\n", o_str_exp);
	printf("Ошибка(обратный) = %f\n", o_obr_exp);
	printf("Ошибка(попарный) = %f\n\n", o_par_exp);
	return 0;
}