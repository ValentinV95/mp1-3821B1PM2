#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

float sum_par(float* mas, int size)
{
	int i,a,k;
	float res = 0.f;
	float* arr;
	if (size % 2 == 0)
	{
		a = size / 2;
		arr = (float*)malloc(a * sizeof(float));
		for (i = 0, k = 0; i < a; i++, k += 2)
		{
			arr[i] = mas[k] + mas[k + 1];
		}
	}
	else
	{
		a = ((size - 1) / 2) + 1;
		arr = (float*)malloc(a * sizeof(float));
		for (i = 0, k = 0; i < (a-1); i++, k += 2)
		{
			arr[i] = mas[k] + mas[k + 1];
		}
		arr[a - 1] = mas[size - 1];
	}
	for (i = a-1; i >= 0; i--)
	{
		res += arr[i];
	}
	return res;
}

float sum_back(float* mas, int size)
{
	int i;
	float res = 0.f;
	for (i = size-1; i >= 0; i--)
	{
		res += mas[i];
	}
	return res;
}

float sum_str(float* mas, int size)
{
	int i;
	float res = 0.f;
	for (i = 0; i < size; i++)
	{
		res += mas[i];
	}
	return res;
}

float exp_sled(float x, int i, float pred)
{
	int n = i;
	return pred * x / n;
}

float ln_sled(float x, int i, float pred)
{
	int n = i;
	return (-1.f) * pred * x * n  / (n + 1.f);
}

float cos_sled(float x, int i, float pred)
{
	int n = 2 * i;
	return (-1.f) * pred * (x * x) / (n * (n - 1.f));
}

float sin_sled(float x, int i, float pred)
{
	int n = 2 * i + 1;
	return (-1.f) * pred * (x * x) / (n * (n - 1.f));
}

void mas_f(int size, float* mas, float (*sled)(float, int, float), float x)
{
	int i;
	float pred = mas[0];
	for (i = 1; i < size; i++)
	{
		mas[i] = sled(x, i, pred);
		pred = mas[i];
	}
}

void mistake(float res, float res_math)
{
	float mistake;
	mistake = 100.f - ((res / res_math) * 100.f);
	printf("\nОшибка = %.16f", mistake);
}


int main()
{
	float x, a, res, res_math, y;
	const float PI = 3.14159265f;
	int size;
	float* mas;
	setlocale(LC_ALL, "Russian");
	printf("Введите количество элементов ряда: ");
	scanf_s("%d", &size);
	mas = (float*)malloc(size * sizeof(float));
	printf("Введите x: ");
	scanf_s("%f", &x);

	//ln(1 + x)
	if ((x > -1) && (x < 1))
	{
		mas[0] = x;
		y = 1 + x;
		res_math = (float)log(y);
		printf("\n\nln(1 + x) = %.16f", res_math);
		mas_f(size, mas, ln_sled, x);
		res = sum_str(mas, size);
		printf("\nПрямая сумма = %.16f", res);
		mistake(res, res_math);
		res = sum_back(mas, size);
		printf("\nОбратная сумма = %.16f", res);
		mistake(res, res_math);
		res = sum_par(mas, size);
		printf("\nПопарная сумма = %.16f", res);
		mistake(res, res_math);
	}
	else
	{
		printf("x не входит в область определения функции ln(1+x)");
	}
	
	//exp
	mas[0] = 1.f;
	res_math = (float)exp(x);
	printf("\n\nexp x = %.16f", res_math);
	mas_f(size, mas, exp_sled, x);
	res = sum_str(mas, size);
	printf("\nПрямая сумма = %.16f", res);
	mistake(res, res_math);
	res = sum_back(mas, size);
	printf("\nОбратная сумма = %.16f", res);
	mistake(res, res_math);
	res = sum_par(mas, size);
	printf("\nПопарная сумма = %.16f", res);
	mistake(res, res_math);

	for (a = 2.f * PI; x < 0.f;)
	{
		x += a;
	}
	for (a = 2.f * PI; x > a;)
	{
		x -= a;
	}

	//sin
	mas[0] = x;
	res_math = (float)sin(x);
	printf("\n\nsin x = %.16f", res_math);
	mas_f(size, mas, sin_sled, x);
	res = sum_str(mas, size);
	printf("\nПрямая сумма = %.16f", res);
	mistake(res, res_math);
	res = sum_back(mas, size);
	printf("\nОбратная сумма = %.16f", res);
	mistake(res, res_math);
	res = sum_par(mas, size);
	printf("\nПопарная сумма = %.16f", res);
	mistake(res, res_math);

	//cos
	mas[0] = 1.f;
	res_math = (float)cos(x);
	printf("\n\ncos x = %.16f", res_math);
	mas_f(size, mas, cos_sled, x);
	res = sum_str(mas, size);
	printf("\nПрямая сумма = %.16f", res);
	mistake(res, res_math);
	res = sum_back(mas, size);
	printf("\nОбратная сумма = %.16f", res);
	mistake(res, res_math);
	res = sum_par(mas, size);
	printf("\nПопарная сумма = %.16f", res);
	mistake(res, res_math);
	return 0;
}