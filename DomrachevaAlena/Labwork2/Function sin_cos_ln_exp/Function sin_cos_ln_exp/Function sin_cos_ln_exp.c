#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

float exp_par(float x)
{
	float exp_res = 0.f;
	const int size = 100;
	float mas[100],arr[50];
	float n = 1.f;
	float pred = 1.f, sled;
	int i,k;
	mas[0] = 1.f;
	for (i = 1; i < size; i++)
	{
		sled = x / n;
		mas[i] = (float)(pred * sled);
		pred *= sled;
		n += 1.f;
	}
	for (i = 0, k = 0; i < 50; i++, k += 2)
	{
		arr[i] = mas[k] + mas[k + 1];
	}
	for (i = 49; i >= 0; i--)
	{
		exp_res += arr[i];
	}
	return exp_res;
}
float exp_back(float x)
{
	float exp_res = 0.f;
	const int size = 100;
	float mas[100];
	float n = 1.f;
	float pred = 1.f, sled;
	int i;
	mas[0] = 1.f;
	for (i = 1; i < size; i++)
	{
		sled = x / n;
		mas[i] = (float)(pred * sled);
		pred *= sled;
		n += 1.f;
	}
	for (i = size - 1; i >= 0; i--)
	{
		exp_res += mas[i];
	}
	return exp_res;
}
float exp_str(float x)
{
	float exp_res = 0.f;
	const int size = 100;
	float mas[100];
	float n = 1.f;
	float pred = 1.f, sled;
	int i;
	mas[0] = 1.f;
	for (i = 1; i < size; i++)
	{
		sled = x / n;
		mas[i] = (float)(pred * sled);
		pred *= sled;
		n += 1.f;
	}
	for (i = 0; i < size; i++)
	{
		exp_res += mas[i];
	}
	return exp_res;
}
float ln_par(float x)
{
	float ln_res = 0.f;
	const int size = 100;
	float mas[100], arr[50];
	float n = 1.f;
	float pred = x, sled;
	int i, k;
	mas[0] = x;
	for (i = 1; i < size; i++)
	{
		sled = x / (n + 1.f);
		mas[i] = (float)(pow(-1.f, i) * pred * sled);
		pred *= x;
		n += 1.f;
	}
	for (i = 0, k = 0; i < 50; i++, k += 2)
	{
		arr[i] = mas[k] + mas[k + 1];
	}
	for (i = 49; i >= 0; i--)
	{
		ln_res += arr[i];
	}
	return ln_res;
}
float ln_back(float x)
{
	float ln_res = 0.f;
	const int size = 100;
	float mas[100];
	float n = 1.f;
	float pred = x, sled;
	int i;
	mas[0] = x;
	for (i = 1; i < size; i++)
	{
		sled = x / (n + 1.f);
		mas[i] = (float)(pow(-1.f, i) * pred * sled);
		pred *= x;
		n += 1.f;
	}
	for (i = size - 1; i >= 0; i--)
	{
		ln_res += mas[i];
	}
	return ln_res;
}
float ln_str(float x)
{
	float ln_res = 0.f;
	const int size = 100;
	float mas[100];
	float n = 1.f;
	float pred = x, sled;
	int i;
	mas[0] = x;
	for (i = 1; i < size; i++)
	{
		sled = x / (n + 1.f);
		mas[i] = (float)(pow(-1.f, i) * pred * sled);
		pred *= x;
		n += 1.f;
	}
	for (i = 0; i < size; i++)
	{
		ln_res += mas[i];
	}
	return ln_res;
}
float cos_par(float x)
{
	const float PI = 3.14159265f;
	const int size = 100;
	float mas[100], arr[50];
	float a, sled;
	int i, k;
	float n = 1.f;
	float pred = 1.f;
	float cos_res = 0.f;
	mas[0] = 1.f;
	for (a = 2.f * PI; x < 0.f;)
	{
		x += a;
	}
	for (a = 2.f * PI; x > a;)
	{
		x -= a;
	}
	for (i = 1; i < size; i++)
	{
		sled = (x * x) / (n * (n + 1.f));
		mas[i] = (float)(pow(-1.f, i) * pred * sled);
		pred *= sled;
		n += 2.f;
	}
	for (i = 0, k = 0; i < 50; i++, k += 2)
	{
		arr[i] = mas[k] + mas[k + 1];
	}
	for (i = 49; i >= 0; i--)
	{
		cos_res += arr[i];
	}
	return cos_res;
}
float cos_back(float x)
{
	const float PI = 3.14159265f;
	const int size = 100;
	float mas[100];
	float a, sled;
	int i;
	float n = 1.f;
	float pred = 1.f;
	float cos_res = 0.f;
	mas[0] = 1.f;
	for (a = 2.f * PI; x < 0.f;)
	{
		x += a;
	}
	for (a = 2.f * PI; x > a;)
	{
		x -= a;
	}
	for (i = 1; i < size; i++)
	{
		sled = (x * x) / (n * (n + 1.f));
		mas[i] = (float)(pow(-1.f, i) * pred * sled);
		pred *= sled;
		n += 2.f;
	}
	for (i = size - 1; i >= 0; i--)
	{
		cos_res += mas[i];
	}
	return cos_res;
}
float cos_str(float x)
{
	const float PI = 3.14159265f;
	const int size = 100;
	float mas[100];
	float a, sled;
	int i;
	float n = 1.f;
	float pred = 1.f;
	float cos_res = 0.f;
	mas[0] = 1.f;
	for (a = 2.f * PI; x < 0.f;)
	{
		x += a;
	}
	for (a = 2.f * PI; x > a;)
	{
		x -= a;
	}
	for (i = 1; i < size; i++)
	{
		sled = (x * x) / (n * (n + 1.f));
		mas[i] = (float)(pow(-1, i) * pred * sled);
		pred *= sled;
		n += 2.f;
	}
	for (i = 0; i < size; i++)
	{
		cos_res += mas[i];
	}
	return cos_res;
}
float sin_par(float x)
{
	const float PI = 3.14159265f;
	const int size = 100;
	float mas[100], arr[50];
	float a, sled;
	int i, k;
	float n = 1.f;
	float pred;
	float sin_res = 0.f;
	for (a = 2.f * PI; x < 0.f;)
	{
		x += a;
	}
	for (a = 2.f * PI; x > a;)
	{
		x -= a;
	}
	pred = x;
	mas[0] = x;
	for (i = 1; i < size; i++)
	{
		sled = (x * x) / ((n + 1.f) * (n + 2.f));
		mas[i] = (float)(pow(-1, i) * pred * sled);
		pred *= sled;
		n += 2.f;
	}
	for (i = 0, k = 0; i < 50; i++, k += 2)
	{
		arr[i] = mas[k] + mas[k + 1];
	}
	for (i = 49; i >= 0; i--)
	{
		sin_res += arr[i];
	}
	return sin_res;
}
float sin_back(float x)
{
	const float PI = 3.14159265f;
	const int size = 100;
	float mas[100];
	float a, sled;
	int i;
	float n = 1.f;
	float pred;
	float sin_res = 0.f;
	for (a = 2.f * PI; x < 0.f;)
	{
		x += a;
	}
	for (a = 2.f * PI; x > a;)
	{
		x -= a;
	}
	pred = x;
	mas[0] = x;
	for (i = 1; i < size; i++)
	{
		sled = (x * x) / ((n + 1.f) * (n + 2.f));
		mas[i] = (float)(pow(-1.f, i) * pred * sled);
		pred *= sled;
		n += 2.f;
	}
	for (i = size - 1; i >= 0; i--)
	{
		sin_res += mas[i];
	}
	return sin_res;
}
float sin_str(float x)
{
	const float PI = 3.14159265f;
	const int size = 100;
	float mas[100];
	float a, sled;
	int i;
	float n = 1.f;
	float pred;
	float sin_res = 0.f;
	for (a = 2.f * PI; x < 0.f;)
	{
		x += a;
	}
	for (a = 2.f * PI; x > a;)
	{
		x -= a;
	}
	pred = x;
	mas[0] = x;
	for (i = 1; i < size; i++)
	{
		sled = (x * x) / ((n + 1.f) * (n + 2.f));
		mas[i] = (float)(pow(-1.f, i) * pred * sled);
		pred *= sled;
		n += 2.f;
	}
	for (i = 0; i < size; i++)
	{
		sin_res += mas[i];
	}
	return sin_res;
}
int main()
{
	float x, y;
	float sin_result, sin_math, sin_result_obr,sin_result_par, o_str_sin, o_obr_sin, o_par_sin;
	float cos_result, cos_math, cos_result_obr,cos_result_par, o_str_cos, o_obr_cos, o_par_cos;
	float ln_result, ln_math, ln_result_obr,ln_result_par, o_str_ln, o_obr_ln, o_par_ln;
	float exp_result, exp_math, exp_result_obr,exp_result_par, o_str_exp, o_obr_exp, o_par_exp;
	setlocale(LC_ALL, "Russian");
	printf("Введите x:\n");
	scanf_s("%f", &x);

	sin_result = sin_str(x);
	printf("sin_прямой = %f\n", sin_result);
	sin_result_obr = sin_back(x);
	printf("sin_обратный = %f\n", sin_result_obr);
	sin_result_par = sin_par(x);
	printf("sin_попарный = %f\n", sin_result_par);
	sin_math = sin(x);
	printf("sin_math = %f\n", sin_math);
	o_str_sin = sin_result - sin_math;
	o_obr_sin = sin_result_obr - sin_math;
	o_par_sin = sin_result_par - sin_math;
	printf("Ошибка(прямой) = %f\n", o_str_sin);
	printf("Ошибка(обратный) = %f\n", o_obr_sin);
	printf("Ошибка(попарный) = %f\n\n", o_par_sin);

	cos_result = cos_str(x);
	printf("cos_прямой = %f\n", cos_result);
	cos_result_obr = cos_back(x);
	printf("cos_обратный = %f\n", cos_result_obr);
	cos_result_par = cos_par(x);
	printf("cos_попарный = %f\n", cos_result_par);
	cos_math = cos(x);
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
		ln_result = ln_str(x);
		printf("ln_прямой = %f\n", ln_result);
		ln_result_obr = ln_back(x);
		printf("ln_обратный = %f\n", ln_result_obr);
		ln_result_par = ln_par(x);
		printf("ln_попарный = %f\n", ln_result_par);
		ln_math = log(y);
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

	exp_result = exp_str(x);
	printf("exp_прямой = %f\n", exp_result);
	exp_result_obr = exp_back(x);
	printf("exp_обратный = %f\n", exp_result_obr);
	exp_result_par = exp_par(x);
	printf("exp_попарный = %f\n", exp_result_par);
	exp_math = exp(x);
	printf("exp_math = %f\n", exp_math);
	o_str_exp = exp_result - exp_math;
	o_obr_exp = exp_result_obr - exp_math;
	o_par_exp = exp_result_par - exp_math;
	printf("Ошибка(прямой) = %f\n", o_str_exp);
	printf("Ошибка(обратный) = %f\n", o_obr_exp);
	printf("Ошибка(попарный) = %f\n\n", o_par_exp);
	return 0;
}