#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

double exp_back(double x)
{
	double exp_res = 0;
	const int size = 100;
	double mas[100];
	double n = 1.0;
	double pred = 1.0;
	mas[0] = 1.0;
	for (int i = 1; i < size; i++)
	{
		double sled = x / n;
		mas[i] = pred * sled;
		pred *= sled;
		n += 1.0;
	}
	for (int i = size - 1; i >= 0; i--)
	{
		exp_res += mas[i];
	}
	return exp_res;
}
double exp_str(double x)
{
	double exp_res = 0;
	const int size = 100;
	double mas[100];
	double n = 1.0;
	double pred = 1.0;
	mas[0] = 1.0;
	for (int i = 1; i < size; i++)
	{
		double sled = x / n;
		mas[i] = pred * sled;
		pred *= sled;
		n += 1.0;
	}
	for (int i = 0; i < size; i++)
	{
		exp_res += mas[i];
	}
	return exp_res;
}

double ln_back(double x)
{
	double ln_res = 0;
	const int size = 100;
	double mas[100];
	double n = 1.0;
	double pred = x;
	mas[0] = x;
	for (int i = 1; i < size; i++)
	{
		double sled = x / (n + 1);
		mas[i] = pow(-1, i) * pred * sled;
		pred *= x;
		n += 1.0;
	}
	for (int i = size - 1; i >= 0; i--)
	{
		ln_res += mas[i];
	}
	return ln_res;
}
double ln_str(double x)
{
	double ln_res = 0;
	const int size = 100;
	double mas[100];
	double n = 1.0;
	double pred = x;
	mas[0] = x;
	for (int i = 1; i < size; i++)
	{
		double sled = x / (n + 1);
		mas[i] = pow(-1,i) * pred * sled;
		pred *= x;
		n += 1.0;
	}
	for (int i = 0; i < size; i++)
	{
		ln_res += mas[i];
	}
	return ln_res;
}

double cos_back(double x)
{
	const double PI = 3.141592653589793238462643383279502884;
	const int size = 100;
	double mas[100];
	double cos_res = 0;
	for (double i = 2.0 * PI; x < 0.0;)
	{
		x += i;
	}
	for (double i = 2.0 * PI; x > i;)
	{
		x -= i;
	}
	mas[0] = 1.0;
	double n = 1.0;
	double pred = 1.0;
	for (int i = 1; i < size; i++)
	{
		double sled = (x * x) / ( n * (n + 1.0));
		mas[i] = pow(-1, i) * pred * sled;
		pred *= sled;
		n += 2.0;
	}
	for (int i = size - 1; i >= 0; i--)
	{
		cos_res += mas[i];
	}
	return cos_res;
}
double cos_str(double x)
{
	const double PI = 3.141592653589793238462643383279502884;
	const int size = 100;
	double mas[100];
	double cos_res = 0;
	for (double i = 2.0 * PI; x < 0.0;)
	{
		x += i;
	}
	for (double i = 2.0 * PI; x > i;)
	{
		x -= i;
	}
	mas[0] = 1.0;
	double n = 1.0;
	double pred = 1.0;
	for (int i = 1; i < size; i++)
	{
		double sled = (x * x) / (n * (n + 1.0));
		mas[i] = pow(-1, i) * pred * sled;
		pred *= sled;
		n += 2.0;
	}
	for (int i = size - 1; i >= 0; i--)
	{
		cos_res += mas[i];
	}
	return cos_res;
}

double sin_back(double x)
{
	const double PI = 3.141592653589793238462643383279502884;
	const int size = 100;
	double mas[100];
	double sin_res = 0;
	for (double i = 2.0 * PI; x < 0.0;)
	{
		x += i;
	}
	for (double i = 2.0 * PI; x > i;)
	{
		x -= i;
	}
	mas[0] = x;
	double n = 1.0;
	double pred = x;
	for (int i = 1; i < size; i++)
	{
		double sled = (x * x) / ((n + 1.0) * (n + 2.0));
		mas[i] = pow(-1,i)*pred * sled;
		pred *= sled;
		n += 2.0;
	}
	for (int i = size - 1; i >= 0; i--)
	{
		sin_res += mas[i];
	}
	return sin_res;
}
double sin_str(double x)
{
	const double PI = 3.141592653589793238462643383279502884;
	const int size = 100;
	double mas[100];
	double sin_res = 0;
	for (double i = 2.0 * PI; x < 0.0;)
	{
		x += i;
	}
	for (double i = 2.0 * PI; x > i;)
	{
		x -= i;
	}
	mas[0] = x;
	double n = 1.0;
	double pred = x;
	for (int i = 1; i < size; i++)
	{
		double sled = (x * x) / ((n + 1.0) * (n + 2.0));
		mas[i] = pow(-1, i) * pred * sled;
		pred *= sled;
		n += 2.0;
	}
	for (int i = size - 1; i >= 0; i--)
	{
		sin_res += mas[i];
	}
	return sin_res;
}
int main()
{
	double x;
	double sin_result, sin_math, sin_result_obr;
	double cos_result, cos_math, cos_result_obr;
	double ln_result, ln_math, ln_result_obr;
	double exp_result, exp_math, exp_result_obr;
	setlocale(LC_ALL, "Russian");
	printf("Введите x:\n");
	scanf_s("%lf", &x);
	
	sin_result = sin_str(x);
	printf("sin_прямой = %.20lf\n", sin_result);
	sin_result_obr = sin_back(x);
	printf("sin_обратный = %.20lf\n", sin_result_obr);
	sin_math = sin(x);
	printf("sin_math = %.20lf\n", sin_math);
	printf("Ошибка(прямой) = %.20lf\n", sin_result - sin_math);
	printf("Ошибка(обратный) = %.20lf\n\n", sin_result_obr - sin_math);

	cos_result = cos_str(x);
	printf("cos_прямой = %.20lf\n", cos_result);
	cos_result_obr = cos_back(x);
	printf("cos_обратный = %.20lf\n", cos_result_obr);
	cos_math = cos(x);
	printf("cos_math = %.20lf\n", cos_math);
	printf("Ошибка(прямой) = %.20lf\n", cos_result - cos_math);
	printf("Ошибка(обратный) = %.20lf\n\n", cos_result_obr - cos_math);

	if ((x > -1) && (x <= 1))
	{
		ln_result = ln_str(x);
		printf("ln_прямой = %.20lf\n", ln_result);
		ln_result_obr = ln_back(x);
		printf("ln_обратный = %.20lf\n", ln_result_obr);
		ln_math = log(1 + x);
		printf("ln_math = %.20lf\n", ln_math);
		printf("Ошибка(прямой) = %.20lf\n", ln_result - ln_math);
		printf("Ошибка(обратный) = %.20lf\n\n", ln_result_obr - ln_math);
	}
	else
	{
		printf("x не удовлетворяет области определения\n\n");
	}

	exp_result = exp_str(x);
	printf("exp_прямой = %.20lf\n", exp_result);
	exp_result_obr = exp_back(x);
	printf("exp_обратный = %.20lf\n", exp_result_obr);
	exp_math = exp(x);
	printf("exp_math = %.20lf\n", exp_math);
	printf("Ошибка(прямой) = %.20lf\n", exp_result - exp_math);
	printf("Ошибка(обратный) = %.20lf\n\n", exp_result_obr - exp_math);
	return 0;
}